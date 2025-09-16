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

	if (MyItemData->ItemCategory == EItemCategory::Consumable) // �Ҹ�ǰ ����
	{
		if (PlayerState->RemoveCoins(MyItemData->Price))
		{
			// TODO: PlayerCharacter�� HP�� ȸ����Ű�� �Լ��� ȣ��
			UE_LOG(LogTemp, Log, TEXT("%s Buy Success. HP %f Healing"), *MyItemData->ItemName.ToString(), MyItemData->HealthToRestore);
		}
	}
	else if (MyItemData->ItemCategory == EItemCategory::Upgrade) // ���׷��̵�
	{
		// TODO: PlayerCharacter���� ���� ���׷��̵� ������ ��������
		// int32 CurrentLevel = PlayerCharacter->GetUpgradeLevel(MyItemData->UpgradeType);
		int32 CurrentLevel = 0; // �ӽ� ��

		if (CurrentLevel >= MyItemData->MaxLevel)
		{
			UE_LOG(LogTemp, Log, TEXT("%s level is max"), *MyItemData->ItemName.ToString());
			// TODO: �ִ� ������ �� ��ư ��Ȱ��ȭ ó��
			return;
		}

		if (PlayerState->RemoveCoins(MyItemData->Price))
		{
			// TODO: PlayerCharacter�� ���� �ɷ�ġ�� �����ϴ� �Լ��� ȣ��
			// PlayerCharacter->ApplyUpgrade(MyItemData->UpgradeType, MyItemData->UpgradeValuePerLevel);
			UE_LOG(LogTemp, Log, TEXT("%s upgrade success."), *MyItemData->ItemName.ToString());

			// TODO: ���׷��̵� �� UI (����, ���� ǥ�� ��) ���ΰ�ħ
		}
	}
}
