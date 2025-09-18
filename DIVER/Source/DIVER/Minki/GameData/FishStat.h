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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Information)
	FText Description;
public:

	UPROPERTY(EditAnywhere, Category = Fish)
	TObjectPtr<class USkeletalMesh> FishMesh;

	UPROPERTY(EditAnywhere, Category = Fish)
	TSubclassOf<class AFishAIController> FishController;

	UPROPERTY(EditAnywhere, Category = Animation)
	TSubclassOf<class UFishAnimInstance> FishAnimInstance;

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Swim)
	float MinHeight = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Swim)
	float MaxHeight = 0.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ChasingSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange = 0.0f;
};
