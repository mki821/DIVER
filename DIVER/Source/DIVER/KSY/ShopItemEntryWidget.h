#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopItemEntryWidget.generated.h"

struct FShopItemData;
class UTextBlock;
class UButton;
class UImage;

UCLASS()
class DIVER_API UShopItemEntryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup(const FShopItemData* ItemData);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UImage* ItemIcon;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ItemNameText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ItemPriceText;
	UPROPERTY(meta = (BindWidget)) UButton* ActionButton;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ActionButtonText;

private:
	const FShopItemData* MyItemData;

	UFUNCTION()
	void OnActionButtonClicked();
};
