// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Minki/Interface/DamageableInterface.h"
#include "Minki/GameData/FishStat.h"
#include "FishBase.generated.h"

DECLARE_DELEGATE(FDeadDelegate)
DECLARE_DELEGATE(FAIAttackFinished)

UCLASS()
class DIVER_API AFishBase : public APawn, public IDamageableInterface
{
	GENERATED_BODY()
	
public:	
	AFishBase();

protected:
	virtual void BeginPlay() override;

	void Dead();

public:
	void Initialize();

	virtual void TakeDamage(float Damage);

	void AttackHitCheck();

	void Attack(FAIAttackFinished InOnAttackFinished);
	void AttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded);

public:
	void SetFishData(TObjectPtr<UFishStat> NewFishData) { FishData = NewFishData; }
	void SetChasing(bool IsChasing);

public:
	FDeadDelegate DeadEvent;

protected:
	UPROPERTY(EditAnywhere, Category = Fish)
	TObjectPtr<class UFishStat> FishData;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> Mesh;

private:
	float CurrentHp = 0;

	FAIAttackFinished OnAttackFinished;
};
