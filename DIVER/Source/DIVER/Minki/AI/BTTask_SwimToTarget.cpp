// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_SwimToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SwimToTarget::UBTTask_SwimToTarget()
{
	NodeName = TEXT("SwimToTarget");
}

EBTNodeResult::Type UBTTask_SwimToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));
	if(Target == nullptr)
		return EBTNodeResult::Failed;

	FVector TargetPosition = Cast<AActor>(Target)->GetActorLocation();
	float Speed = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Speed"));

	FVector ControllingPawnLocation = ControllingPawn->GetActorLocation();

	FVector Direction = TargetPosition - ControllingPawnLocation;
	Direction.Normalize();

	FQuat Quat = FQuat::Slerp(ControllingPawn->GetActorQuat(), Direction.ToOrientationQuat(), 0.1f);

	ControllingPawn->SetActorLocationAndRotation(ControllingPawnLocation + Direction * Speed, Quat.Rotator());

	return EBTNodeResult::Succeeded;
}
