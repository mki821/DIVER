#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ShopItemData.generated.h"

// ������ ����
UENUM(BlueprintType)
enum class EItemType : uint8
{
	Consumable	UMETA(DisplayName = "Consumable"),
	Upgrade		UMETA(DisplayName = "Upgrade")
};

// � �ɷ�ġ�� ���׷��̵�����
UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	None			UMETA(DisplayName = "None"),
	MaxOxygen		UMETA(DisplayName = "MaxOxygen"),
	SwimSpeed		UMETA(DisplayName = "MoveSpeed")
};

USTRUCT(BlueprintType)
struct FShopItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Price;

	// - �Ҹ�ǰ ���� ������ -
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ItemType == EItemType::Consumable"))
	float HealthToRestore;

	// - ���׷��̵� ���� ������ -
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ItemType == EItemType::Upgrade"))
	EUpgradeType UpgradeType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ItemType == EItemType::Upgrade"))
	float UpgradeValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ItemType == EItemType::Upgrade"))
	int32 MaxLevel;
};