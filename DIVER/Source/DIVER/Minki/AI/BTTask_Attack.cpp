// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_Attack.h"
#include "AIController.h"
#include "Minki/Fish/FishBase.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	// 공격 구현
	AFishBase* Fish = Cast<AFishBase>(ControllingPawn);
	if (Fish == nullptr)
		return EBTNodeResult::Failed;

	FAIAttackFinished OnAttackFinished;
	OnAttackFinished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	Fish->Attack(OnAttackFinished);
	return EBTNodeResult::InProgress;
}
