// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/Animation/AnimNotify_AttackHitCheck.h"
#include "Minki/Fish/FishBase.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		// 주인공 캐릭터에서 충돌 판정
		AFishBase* Fish = Cast<AFishBase>(MeshComp->GetOwner());
		if (Fish)
		{
			Fish->AttackHitCheck();
		}
	}
}
