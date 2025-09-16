// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/AI/BTService_DetectTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"
#include "DrawDebugHelpers.h"

UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = "DetectTarget";
	Interval = 0.5f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return;

	UWorld* World = ControllingPawn->GetWorld();
	if (World == nullptr)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(ControllingPawn);

	FVector Location = ControllingPawn->GetActorLocation();

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(DetectRange),
		CollisionParams
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* TargetPawn = Cast<APawn>(OverlapResult.GetActor());
			if (TargetPawn && TargetPawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), TargetPawn);
#if ENABLE_DRAW_DEBUG
				DrawDebugSphere(World, Location, DetectRange, 16, FColor::Green, false, 0.2f);
#endif
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
#if ENABLE_DRAW_DEBUG
	DrawDebugSphere(World, Location, DetectRange, 16, FColor::Red, false, 0.2f);
#endif
}
