#include "KSY/SellFishEntryWidget.h"
#include "KSY/FishData.h"
#include "KSY/DiverPlayerState.h" 
#include "YTH/Diver/DiverCharacter.h"
#include "YTH/Diver/DiverPlayerController.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "KSY/ShopWidget.h"

void USellFishEntryWidget::Setup(const FFishData* FishData, int32 Quantity)
{
	MyFishData = FishData;
	MyQuantity = Quantity;

	if (!MyFishData) return;

	if (FishIcon && !MyFishData->FishIcon.IsNull())
	{
		FishIcon->SetBrushFromTexture(MyFishData->FishIcon.LoadSynchronous());
	}

	if (FishNameText)
	{
		FishNameText->SetText(MyFishData->FishName);
	}

	if (FishPriceText)
	{
		FishPriceText->SetText(FText::AsNumber(MyFishData->SellPrice));
	}

	if (FishQuantityText)
	{
		FishQuantityText->SetText(FText::Format(FText::FromString(TEXT("Have: {0}")), MyQuantity));
	}
}

void USellFishEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SellButton)
	{
		SellButton->OnClicked.AddDynamic(this, &USellFishEntryWidget::OnSellButtonClicked);
	}
}

void USellFishEntryWidget::OnSellButtonClicked()
{
	if (!MyFishData) return;

	ADiverPlayerState* PlayerState = GetOwningPlayer()->GetPlayerState<ADiverPlayerState>();
	ADiverCharacter* PlayerCharacter = GetOwningPlayerPawn<ADiverCharacter>();

	if (!PlayerState /*|| !PlayerCharacter*/)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState or PlayerCharacter is not valid!"));
		return;
	}

	// TODO: PlayerCharacter�� ����� �κ��丮���� �������� �����ϴ� �Լ��� ȣ��
	// �� �Լ��� ���� �� true, ���� ��(�������� ���� ��� ��) false�� ��ȯ�ؾ� �մϴ�.
	// bool bRemoved = PlayerCharacter->RemoveFromInventory(MyFishData->FishID, 1);
	bool bRemoved = true; // �ӽ�

	if (bRemoved)
	{
		PlayerState->AddCoins(MyFishData->SellPrice);
		UE_LOG(LogTemp, Log, TEXT("%s Success Sell. %d Add Coin."), *MyFishData->FishName.ToString(), MyFishData->SellPrice);

		MyQuantity--;
		if (FishQuantityText)
		{
			FishQuantityText->SetText(FText::Format(FText::FromString(TEXT("Have: {0}")), MyQuantity));
		}

		if (MyQuantity <= 0)
		{
			SetVisibility(ESlateVisibility::Collapsed);
			SellButton->SetIsEnabled(false);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed Remove %s in inventory"), *MyFishData->FishName.ToString());
	}
}
