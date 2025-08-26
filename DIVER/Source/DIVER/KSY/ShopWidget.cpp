#include "KSY/ShopWidget.h"
#include "Components/VerticalBox.h"
#include "Engine/DataTable.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsValid(ShopItemDataTable) || !IsValid(ItemList) || !ShopItemEntryWidgetClass)
	{
		return;
	}

	ItemList->ClearChildren();

	TArray<FName> RowNames = ShopItemDataTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		FShopItemData* ItemData = ShopItemDataTable->FindRow<FShopItemData>(RowName, TEXT(""));
		if (ItemData)
		{
			UUserWidget* ItemEntryWidget = CreateWidget<UUserWidget>(this, ShopItemEntryWidgetClass);
			if (IsValid(ItemEntryWidget))
			{
				// TODO: 생성된 슬롯 위젯에 ItemData 정보를 전달하는 함수 호출
				// Cast<UShopItemEntryWidget>(ItemEntryWidget)->Setup(ItemData);

				ItemList->AddChildToVerticalBox(ItemEntryWidget);
			}
		}
	}
}
