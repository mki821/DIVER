#include "KSY/ShopItemEntryWidget.h"
#include "KSY/ShopItemData.h"
#include "KSY/DiverPlayerState.h"
#include "YTH/Diver/DiverCharacter.h"
#include "YTH/Diver/DiverPlayerController.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UShopItemEntryWidget::Setup(const FShopItemData* ItemData)
{
	MyItemData = ItemData;
	if (!MyItemData) return;

	if (ItemIcon && !MyItemData->ItemIcon.IsNull())
	{
		ItemIcon->SetBrushFromTexture(MyItemData->ItemIcon.LoadSynchronous());
	}

	if (ItemNameText)
	{
		ItemNameText->SetText(MyItemData->ItemName);
	}

	if (ItemPriceText)
	{
		ItemPriceText->SetText(FText::AsNumber(MyItemData->Price));
	}

	if (ActionButtonText)
	{
		if (MyItemData->ItemCategory == EItemCategory::Upgrade)
		{
			ActionButtonText->SetText(FText::FromString(TEXT("Upgrade")));
		}
		else if (MyItemData->ItemCategory == EItemCategory::Consumable)
		{
			ActionButtonText->SetText(FText::FromString(TEXT("Buy")));
		}
	}
}

void UShopItemEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ActionButton)
	{
		ActionButton->OnClicked.AddDynamic(this, &UShopItemEntryWidget::OnActionButtonClicked);
	}
}

void UShopItemEntryWidget::OnActionButtonClicked()
{
	if (!MyItemData) return;

	ADiverPlayerState* PlayerState = GetOwningPlayer()->GetPlayerState<ADiverPlayerState>();
	ADiverCharacter* PlayerCharacter = GetOwningPlayerPawn<ADiverCharacter>();

	if (!PlayerState || PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState or PlayerCharacter is not valid!"));
		return;
	}

	if (PlayerState->GetCurrentCoins() < MyItemData->Price)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Enough Coin"));
		return;
	}

	if (MyItemData->ItemCategory == EItemCategory::Consumable) // 소모품 구매
	{
		if (PlayerState->RemoveCoins(MyItemData->Price))
		{
			// TODO: PlayerCharacter에 HP를 회복시키는 함수를 호출
			UE_LOG(LogTemp, Log, TEXT("%s Buy Success. HP %f Healing"), *MyItemData->ItemName.ToString(), MyItemData->HealthToRestore);
		}
	}
	else if (MyItemData->ItemCategory == EItemCategory::Upgrade) // 업그레이드
	{
		// TODO: PlayerCharacter에서 현재 업그레이드 레벨을 가져오기
		// int32 CurrentLevel = PlayerCharacter->GetUpgradeLevel(MyItemData->UpgradeType);
		int32 CurrentLevel = 0; // 임시 값

		if (CurrentLevel >= MyItemData->MaxLevel)
		{
			UE_LOG(LogTemp, Log, TEXT("%s level is max"), *MyItemData->ItemName.ToString());
			// TODO: 최대 레벨일 때 버튼 비활성화 처리
			return;
		}

		if (PlayerState->RemoveCoins(MyItemData->Price))
		{
			// TODO: PlayerCharacter에 실제 능력치를 적용하는 함수를 호출
			// PlayerCharacter->ApplyUpgrade(MyItemData->UpgradeType, MyItemData->UpgradeValuePerLevel);
			UE_LOG(LogTemp, Log, TEXT("%s upgrade success."), *MyItemData->ItemName.ToString());

			// TODO: 업그레이드 후 UI (가격, 레벨 표시 등) 새로고침
		}
	}
}
