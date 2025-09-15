// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DiverPlayerController.generated.h"

struct FInputActionValue;

/**
 * 
 */


UCLASS()
class DIVER_API ADiverPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADiverPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TurnAction;
};
