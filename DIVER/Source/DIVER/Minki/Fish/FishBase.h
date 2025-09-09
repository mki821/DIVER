// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Minki/GameData/FishStat.h"
#include "FishBase.generated.h"

UCLASS()
class DIVER_API AFishBase : public APawn
{
	GENERATED_BODY()
	
public:	
	AFishBase();

protected:
	virtual void BeginPlay() override;

public:
	void Initialize();

public:
	void SetFishData(TObjectPtr<UFishStat> NewFishData) { FishData = NewFishData; }

protected:
	UPROPERTY(EditAnywhere, Category = Fish)
	TObjectPtr<class UFishStat> FishData;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> Mesh;
};
