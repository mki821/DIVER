// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FishStat.generated.h"

/**
 * 
 */
UCLASS()
class DIVER_API UFishStat : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFishStat() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Information)
	FName Name;

	UPROPERTY(EditAnywhere, Category = Fish)
	TObjectPtr<class USkeletalMesh> FishMesh;

	UPROPERTY(EditAnywhere, Category = Fish)
	TSubclassOf<class AFishAIController> FishController;

	UPROPERTY(EditAnywhere, Category = Fish)
	TSubclassOf<class UFishAnimInstance> FishAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed = 0.0f;
};
