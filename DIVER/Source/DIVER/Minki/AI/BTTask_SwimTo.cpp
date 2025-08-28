// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_SwimTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SwimTo::UBTTask_SwimTo()
{
	NodeName = TEXT("SwimTo");
}

EBTNodeResult::Type UBTTask_SwimTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	FVector PatrolPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PatrolPosition"));
	float Speed = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Speed"));

	FVector ControllingPawnLocation = ControllingPawn->GetActorLocation();

	FVector Direction = PatrolPosition - ControllingPawnLocation;
	Direction.Normalize();

	FQuat Quat = FQuat::Slerp(ControllingPawn->GetActorQuat(), Direction.ToOrientationQuat(), 0.1f);

	ControllingPawn->SetActorLocationAndRotation(ControllingPawnLocation + Direction * Speed, Quat.Rotator());

    return EBTNodeResult::Succeeded;
}
