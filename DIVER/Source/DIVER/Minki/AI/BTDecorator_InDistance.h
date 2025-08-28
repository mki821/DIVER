// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_InDistance.generated.h"

/**
 * 
 */
UCLASS()
class DIVER_API UBTDecorator_InDistance : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_InDistance();

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere)
	float Distance = 100.0f;
};
