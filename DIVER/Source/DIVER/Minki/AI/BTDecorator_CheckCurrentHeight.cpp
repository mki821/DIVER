// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTDecorator_CheckCurrentHeight.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckCurrentHeight::UBTDecorator_CheckCurrentHeight()
{
	NodeName = TEXT("CheckCurrentHeight");
}

bool UBTDecorator_CheckCurrentHeight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!Super::CalculateRawConditionValue(OwnerComp, NodeMemory))
		return false;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return false;

	float CurrentHeight = ControllingPawn->GetActorLocation().Z;
	float MaxHeight = OwnerComp.GetBlackboardComponent()->GetValueAsFloat("MaxHeight");

	return CurrentHeight <= MaxHeight;
}
