// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

UCLASS()
class DIVER_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:
	ATimeManager();

protected:
	virtual void BeginPlay() override;

private:
	void AddTime();

protected:
	UPROPERTY(EditAnywhere, Category = Sun)
	TObjectPtr<class AActor> Sun;

private:
	FTimerHandle TimerHandle;
};
