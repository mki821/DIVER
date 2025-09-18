// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/Fish/FishBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Minki/GameData/FishStat.h"
#include "Minki/AI/FishAIController.h"
#include "Minki/Animation/FishAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DamageEvents.h"
#include "AIController.h"
#include "BrainComponent.h"

AFishBase::AFishBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Fish"));
	Capsule->SetCollisionProfileName(FName("Fish"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	AutoPossessAI = EAutoPossessAI::Disabled;
}

void AFishBase::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void AFishBase::Dead()
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->StopLogic(TEXT("Dead"));
	}

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	UAnimMontage* DeadMontage = FishData->DeadMontage;

	if (AnimInstance && DeadMontage)
	{
		AnimInstance->Montage_Play(DeadMontage);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &AFishBase::DeadEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, DeadMontage);
	}
}

void AFishBase::DeadEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	DeadEvent.ExecuteIfBound();
	Destroy();
}

void AFishBase::Initialize()
{
	if (FishData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FishData is not umm..."));

		return;
	}

	Mesh->SetSkeletalMesh(FishData->FishMesh);
	Mesh->SetAnimInstanceClass(FishData->FishAnimInstance);

	CurrentHp = FishData->MaxHp;

	AFishAIController* FishController = GetWorld()->SpawnActor<AFishAIController>(FishData->FishController);
	if (FishController)
	{
		FishController->Possess(this);

		UBlackboardComponent* BlackboardComponent = FishController->GetBlackboardComponent();
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsFloat(TEXT("MinHeight"), FishData->MinHeight);
			BlackboardComponent->SetValueAsFloat(TEXT("MaxHeight"), FishData->MaxHeight);
		}
	}
}

void AFishBase::Attack(FAIAttackFinished InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	UAnimMontage* AttackMontage = FishData->AttackMontage;

	if (AnimInstance->GetCurrentActiveMontage() == AttackMontage)
		return;

	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &AFishBase::AttackEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
	}
}

void AFishBase::AttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	OnAttackFinished.ExecuteIfBound();
}

void AFishBase::TakeDamage(float Damage)
{
	CurrentHp -= Damage;

	if (CurrentHp <= 0.0f)
	{
		Dead();
	}
}

void AFishBase::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = FishData->AttackRange;
	const float AttackRadius = FishData->AttackRadius;
	const float AttackDamage = FishData->Attack;

	const FVector Start = GetActorLocation() + GetActorForwardVector();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}

void AFishBase::SetChasing(bool IsChasing)
{
	UFishAnimInstance* FishAnimInstance = Cast<UFishAnimInstance>(Mesh->GetAnimInstance());
	if (FishAnimInstance)
	{
		FishAnimInstance->IsChasing = IsChasing;
	}
}
