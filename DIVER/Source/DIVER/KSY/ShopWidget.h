// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KSY/ShopItemData.h"
#include "ShopWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UVerticalBox;
class UDataTable;

UCLASS()
class DIVER_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, Category = "Shop | Data")
	UDataTable* ShopItemDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Shop | Data")
	UDataTable* FishDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Shop | Widget")
	TSubclassOf<class UShopItemEntryWidget> ItemEntryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Shop | Widget")
	TSubclassOf<class USellFishEntryWidget> FishEntryWidgetClass;

	UPROPERTY(meta = (BindWidget)) UButton* UpgradeTabButton;
	UPROPERTY(meta = (BindWidget)) UButton* BuyTabButton;
	UPROPERTY(meta = (BindWidget)) UButton* SellTabButton;

	UPROPERTY(meta = (BindWidget)) UWidgetSwitcher* TabSwitcher;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* UpgradeList;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* BuyList;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* SellList;

private:
	UFUNCTION() void OnUpgradeTabClicked();
	UFUNCTION() void OnBuyTabClicked();
	UFUNCTION() void OnSellTabClicked();

	void PopulateShopLists();

	void PopulateSellList();
};
