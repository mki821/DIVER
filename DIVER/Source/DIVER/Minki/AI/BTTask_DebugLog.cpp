// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTTask_DebugLog.h"

UBTTask_DebugLog::UBTTask_DebugLog()
{
	NodeName = TEXT("DebugLog");
}

EBTNodeResult::Type UBTTask_DebugLog::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	UE_LOG(LogTemp, Display, TEXT("[Debug] %s"), *Format);

	return EBTNodeResult::Succeeded;
}
