// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SwimTo.generated.h"

/**
 * 
 */
UCLASS()
class DIVER_API UBTTask_SwimTo : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SwimTo();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
