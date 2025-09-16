// Fill out your copyright notice in the Description page of Project Settings.


#include "YTH/Diver/DiverCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADiverCharacter::ADiverCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADiverCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADiverCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADiverCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

}

