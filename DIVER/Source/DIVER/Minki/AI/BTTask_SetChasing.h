// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetChasing.generated.h"

/**
 * 
 */
UCLASS()
class DIVER_API UBTTask_SetChasing : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetChasing();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	bool IsChasing;
};
