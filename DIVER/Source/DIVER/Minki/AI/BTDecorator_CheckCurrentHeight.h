// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckCurrentHeight.generated.h"

/**
 * 
 */
UCLASS()
class DIVER_API UBTDecorator_CheckCurrentHeight : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_CheckCurrentHeight();

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
