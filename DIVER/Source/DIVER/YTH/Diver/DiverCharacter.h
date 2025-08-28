// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DiverCharacter.generated.h"

UCLASS()
class DIVER_API ADiverCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADiverCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	class UInputMappingContext* InputContext;
};
