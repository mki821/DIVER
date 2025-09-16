// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_SetChasing.h"
#include "AIController.h"
#include "Minki/Fish/FishBase.h"

UBTTask_SetChasing::UBTTask_SetChasing()
{
	NodeName = TEXT("SetChasing");
}

EBTNodeResult::Type UBTTask_SetChasing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	AFishBase* FishBase = Cast<AFishBase>(ControllingPawn);
	if (FishBase == nullptr)
		return EBTNodeResult::Failed;

	FishBase->SetChasing(IsChasing);

	return EBTNodeResult::Succeeded;
}
