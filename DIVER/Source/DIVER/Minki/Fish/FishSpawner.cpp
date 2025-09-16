// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/Fish/FishSpawner.h"
#include "Minki/Fish/FishBase.h"
#include "Minki/GameData/FishStat.h"

AFishSpawner::AFishSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AFishSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFishSpawner::SpawnFish, 5, true);
}

void AFishSpawner::SpawnFish()
{
	if (CurrentSpawnFishCount >= MaxSpawnFishCount)
	{
		return;
	}

	++CurrentSpawnFishCount;

	AFishBase* NewFish = GetWorld()->SpawnActor<AFishBase>();
	NewFish->SetActorLocation(GetActorLocation());

	NewFish->SetFishData(FishData[0]);
	NewFish->DeadEvent.BindLambda([this]() { --CurrentSpawnFishCount; });

	NewFish->Initialize();
}
