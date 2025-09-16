#include "KSY/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "KSY/DiverPlayerState.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ADiverPlayerState* PlayerState = GetOwningPlayer()->GetPlayerState<ADiverPlayerState>();
	if (PlayerState)
	{
		PlayerState->OnCoinsChanged.AddDynamic(this, &UPlayerHUD::UpdateCoinText);
		UpdateCoinText(PlayerState->GetCurrentCoins());
	}
}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UPlayerHUD::UpdateCoinText(int32 NewCoins)
{
	UE_LOG(LogTemp, Warning, TEXT("Update Coin Text"));

	if (CoinText)
	{
		CoinText->SetText(FText::AsNumber(NewCoins));
	}
}

void UPlayerHUD::UpdateHP(float NewHP)
{
	if (IsValid(HPBar))
	{
		HPBar->SetPercent(NewHP / 100.0f);
	}
}

void UPlayerHUD::UpdateOxygen(float NewOxygen)
{
	if (IsValid(OxygenBar))
	{
		OxygenBar->SetPercent(NewOxygen / 100.0f);
	}
}
