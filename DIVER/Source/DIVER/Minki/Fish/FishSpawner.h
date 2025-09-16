// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FishSpawner.generated.h"

UCLASS()
class DIVER_API AFishSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AFishSpawner();

protected:
	virtual void BeginPlay() override;

private:
	void SpawnFish();

private:
	FTimerHandle TimerHandle;

protected:
	UPROPERTY(EditAnywhere, Category = Fish)
	int MaxSpawnFishCount = 0;

	int CurrentSpawnFishCount = 0;
	
	UPROPERTY(EditAnywhere, Category = Fish)
	TArray<TObjectPtr<class UFishStat>> FishData;
};
