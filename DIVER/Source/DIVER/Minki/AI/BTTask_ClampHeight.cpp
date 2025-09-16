// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_ClampHeight.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClampHeight::UBTTask_ClampHeight()
{
	NodeName = TEXT("ClampHeight");
}

EBTNodeResult::Type UBTTask_ClampHeight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	float MinHeight = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("MinHeight"));
	float MaxHeight = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("MaxHeight"));
	FVector PatrolPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PatrolPosition"));

	float PatrolPositionZ = FMath::Clamp(PatrolPosition.Z, MinHeight, MaxHeight);

	PatrolPosition.Z = PatrolPositionZ;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPosition"), PatrolPosition);

	return EBTNodeResult::Type();
}
