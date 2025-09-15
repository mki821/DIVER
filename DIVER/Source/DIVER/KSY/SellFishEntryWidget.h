// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SellFishEntryWidget.generated.h"

struct FFishData;
class UTextBlock;
class UButton;
class UImage;

UCLASS()
class DIVER_API USellFishEntryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup(const FFishData* FishData, int32 Quantity);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UImage* FishIcon;
	UPROPERTY(meta = (BindWidget)) UTextBlock* FishNameText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* FishPriceText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* FishQuantityText;
	UPROPERTY(meta = (BindWidget)) UButton* SellButton;

private:
	const FFishData* MyFishData;
	int32 MyQuantity;

	UFUNCTION()
	void OnSellButtonClicked();
};
