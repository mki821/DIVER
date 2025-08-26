// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KSY/ShopItemData.h"
#include "ShopWidget.generated.h"

class UDataTable;
class UVerticalBox;

UCLASS()
class DIVER_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shop")
	UDataTable* ShopItemDataTable;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ItemList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shop")
	TSubclassOf<UUserWidget> ShopItemEntryWidgetClass;
};
