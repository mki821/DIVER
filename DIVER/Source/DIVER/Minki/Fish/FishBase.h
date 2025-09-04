// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FishBase.generated.h"

UCLASS()
class DIVER_API AFishBase : public APawn
{
	GENERATED_BODY()
	
public:	
	AFishBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = Fish)
	TObjectPtr<class UFishStat> FishData;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> Mesh;
};
