// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTDecorator_ExistTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_ExistTarget::UBTDecorator_ExistTarget()
{
	NodeName = TEXT("ExistTarget");
}

bool UBTDecorator_ExistTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!Super::CalculateRawConditionValue(OwnerComp, NodeMemory))
		return false;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return false;

	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target") == nullptr)
		return false;

	return true;
}
