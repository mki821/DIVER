// Fill out your copyright notice in the Description page of Project Settings.


#include "YTH/Diver/DiverPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ADiverPlayerController::ADiverPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ADiverPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (auto* Subsystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ADiverPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		&ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this,
		&ThisClass::Input_Turn);
	}
}

void ADiverPlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.X);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.Y);
}
void ADiverPlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	const FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	if (LookAxisVector.X != 0)
	{
		GetPawn()->AddControllerYawInput(LookAxisVector.X	);
	}

	if (LookAxisVector.Y != 0)
	{
		GetPawn()->AddControllerPitchInput(-LookAxisVector.Y);
	}
}
