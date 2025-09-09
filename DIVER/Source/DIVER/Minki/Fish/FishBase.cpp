// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/Fish/FishBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Minki/GameData/FishStat.h"
#include "Minki/AI/FishAIController.h"
#include "Minki/Animation/FishAnimInstance.h"

AFishBase::AFishBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionProfileName(FName("Fish"));
	Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	AutoPossessAI = EAutoPossessAI::Disabled;
}

void AFishBase::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetSkeletalMesh(FishData->FishMesh);
	Mesh->SetAnimInstanceClass(FishData->FishAnimInstance);

	AFishAIController* FishController = GetWorld()->SpawnActor<AFishAIController>(FishData->FishController);
	if (FishController)
	{
		FishController->Possess(this);
	}
}
