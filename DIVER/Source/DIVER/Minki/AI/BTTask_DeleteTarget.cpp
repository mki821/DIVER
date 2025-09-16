// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_DeleteTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_DeleteTarget::UBTTask_DeleteTarget()
{
	NodeName = TEXT("DeleteTarget");
}

EBTNodeResult::Type UBTTask_DeleteTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", nullptr);

	return EBTNodeResult::Succeeded;
}
