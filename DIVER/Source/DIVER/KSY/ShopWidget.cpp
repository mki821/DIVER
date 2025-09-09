#include "KSY/ShopWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Engine/DataTable.h"
#include "KSY/ShopItemData.h"
#include "KSY/ShopItemEntryWidget.h"
#include "KSY/SellFishEntryWidget.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UpgradeTabButton) 
		UpgradeTabButton->OnClicked.AddDynamic(this, &UShopWidget::OnUpgradeTabClicked);
	if (BuyTabButton)     
		BuyTabButton->OnClicked.AddDynamic(this, &UShopWidget::OnBuyTabClicked);
	if (SellTabButton)    
		SellTabButton->OnClicked.AddDynamic(this, &UShopWidget::OnSellTabClicked);

	PopulateShopLists();

	OnUpgradeTabClicked();
}

void UShopWidget::PopulateShopLists()
{
	if (!ShopItemDataTable || !UpgradeList || !BuyList || !ItemEntryWidgetClass) 
		return;

	UpgradeList->ClearChildren();
	BuyList->ClearChildren();

	for (const auto& Row : ShopItemDataTable->GetRowMap())
	{
		FName ItemID = Row.Key;
		FShopItemData* ItemData = (FShopItemData*)Row.Value;

		if (ItemData)
		{
			 UShopItemEntryWidget* Entry = CreateWidget<UShopItemEntryWidget>(this, ItemEntryWidgetClass);
			 if (Entry)
			 {
			 	Entry->Setup(ItemData);
			
			 	if (ItemData->ItemCategory == EItemCategory::Upgrade)
			 	{
			 		UpgradeList->AddChildToVerticalBox(Entry);
			 	}
			 	else if (ItemData->ItemCategory == EItemCategory::Consumable)
			 	{
			 		BuyList->AddChildToVerticalBox(Entry);
			 	}
			 }
		}
	}
}

void UShopWidget::PopulateSellList()
{
	if (!FishDataTable || !SellList || !FishEntryWidgetClass) return;

	SellList->ClearChildren();

	// TODO: 플레이어가 물고기를 잡으면 저장해두고 그 정보를 읽어와야함
	// TMap<FName, int32> PlayerFishInventory = GetOwningPlayerPawn<AMyPlayer>()->GetFishInventory();
	//
	// for (const auto& FishPair : PlayerFishInventory)
	// {
	//		FName FishID = FishPair.Key;
	//		int32 Quantity = FishPair.Value;
	//      
	//      FFishData* FishData = FishDataTable->FindRow<FFishData>(FishID, TEXT(""));
	//      if(FishData)
	//      {
	//			USellFishEntryWidget* Entry = CreateWidget<USellFishEntryWidget>(this, FishEntryWidgetClass);
	//			if(Entry)
	//			{
	//				Entry->Setup(FishData, Quantity);
	//				SellList->AddChildToVerticalBox(Entry);
	//			}
	//      }
	// }
}

void UShopWidget::OnUpgradeTabClicked()
{
	if (TabSwitcher) 
		TabSwitcher->SetActiveWidget(UpgradeList);
}

void UShopWidget::OnBuyTabClicked()
{
	if (TabSwitcher) 
		TabSwitcher->SetActiveWidget(BuyList);
}

void UShopWidget::OnSellTabClicked()
{
	if (TabSwitcher)
	{
		TabSwitcher->SetActiveWidget(SellList);
		PopulateSellList();
	}
}