#include "KSY/KSYGameMode.h"
#include "KSY/DiverPlayerState.h"
#include "KSY/KSYCharacter.h"

AKSYGameMode::AKSYGameMode()
{
    PlayerStateClass = ADiverPlayerState::StaticClass();
}
