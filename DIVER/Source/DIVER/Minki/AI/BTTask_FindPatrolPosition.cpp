// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_FindPatrolPosition.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPosition::UBTTask_FindPatrolPosition()
{
	NodeName = TEXT("FindPatrolPosition");
}

EBTNodeResult::Type UBTTask_FindPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	FVector ControllingPawnLocation = ControllingPawn->GetActorLocation();
	FVector NextPatrolPosition = ControllingPawnLocation + FMath::VRand() * FMath::FRandRange(0.0f, PatrolRadius);

	FHitResult Result;
	if (GetWorld()->LineTraceSingleByChannel(Result, ControllingPawnLocation, NextPatrolPosition, ECC_GameTraceChannel2))
	{
		NextPatrolPosition = Result.Location;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPosition"), NextPatrolPosition);

	return EBTNodeResult::Succeeded;
}
