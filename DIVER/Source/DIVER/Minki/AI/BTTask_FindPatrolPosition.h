// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPosition.generated.h"

/**
 * 
 */
UCLASS()
class DIVER_API UBTTask_FindPatrolPosition : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindPatrolPosition();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	float PatrolRadius = 1000.0f;

private:
	FVector Debug;
};
