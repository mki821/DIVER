// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_SetSpeed.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Minki/Fish/FishBase.h"

UBTTask_SetSpeed::UBTTask_SetSpeed()
{
	NodeName = TEXT("SetSpeed");
}

EBTNodeResult::Type UBTTask_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	AFishBase* Fish = Cast<AFishBase>(OwnerComp.GetAIOwner()->GetPawn());
	if(Fish == nullptr)
		return EBTNodeResult::Failed;

	float Speed = Type == 0 ? Fish->GetFishData()->MovementSpeed : Fish->GetFishData()->ChasingSpeed;
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat("Speed", Speed);

	return EBTNodeResult::Succeeded;
}
