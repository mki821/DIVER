// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/Time/TimeManager.h"

ATimeManager::ATimeManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATimeManager::AddTime, 5, true);
}

void ATimeManager::AddTime()
{
	FRotator CurrentRotation = Sun->GetActorRotation();
	CurrentRotation.Pitch += 15.0f;
	Sun->SetActorRotation(CurrentRotation);
}
