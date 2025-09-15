#include "KSY/DiverPlayerState.h"
#include "Net/UnrealNetwork.h"

ADiverPlayerState::ADiverPlayerState()
{
	CurrentCoins = 5000;
}

void ADiverPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADiverPlayerState, CurrentCoins);
}

void ADiverPlayerState::AddCoins(int32 Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Add Coin"));

	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentCoins += Amount;
		OnCoinsChanged.Broadcast(CurrentCoins);
	}
}

bool ADiverPlayerState::RemoveCoins(int32 Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Use Coin"));

	if (GetLocalRole() == ROLE_Authority)
	{
		if (CurrentCoins >= Amount)
		{
			CurrentCoins -= Amount;
			OnCoinsChanged.Broadcast(CurrentCoins);
			return true;
		}
	}
	return false;
}

int32 ADiverPlayerState::GetCurrentCoins() const
{
	return CurrentCoins;
}

void ADiverPlayerState::OnRep_CurrentCoins()
{
	OnCoinsChanged.Broadcast(CurrentCoins);
}
