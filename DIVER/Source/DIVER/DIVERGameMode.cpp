// Copyright Epic Games, Inc. All Rights Reserved.

#include "DIVERGameMode.h"
#include "DIVERCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADIVERGameMode::ADIVERGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
