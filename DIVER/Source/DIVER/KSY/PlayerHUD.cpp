#include "KSY/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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
