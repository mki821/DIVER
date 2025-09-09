// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/Fish/FishBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Minki/GameData/FishStat.h"
#include "Minki/AI/FishAIController.h"
#include "Minki/Animation/FishAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

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

void AFishBase::Initialize()
{
	if (FishData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FishData is not umm..."));

		return;
	}

	Mesh->SetSkeletalMesh(FishData->FishMesh);
	Mesh->SetAnimInstanceClass(FishData->FishAnimInstance);

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
