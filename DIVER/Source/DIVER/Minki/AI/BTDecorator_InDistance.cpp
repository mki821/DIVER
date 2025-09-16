// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTDecorator_InDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_InDistance::UBTDecorator_InDistance()
{
	NodeName = TEXT("InDistance");
}

bool UBTDecorator_InDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return false;

	FVector PatrolPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PatrolPosition"));

	return FVector::Distance(ControllingPawn->GetActorLocation(), PatrolPosition) <= Distance;
}
