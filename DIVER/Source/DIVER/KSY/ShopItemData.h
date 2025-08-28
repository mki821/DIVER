#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ShopItemData.generated.h"

// 아이템 종류
UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Consumable	UMETA(DisplayName = "Consumable"),
	Upgrade		UMETA(DisplayName = "Upgrade")
};

// 어떤 능력치를 업그레이드할지
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
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemCategory ItemCategory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Price;

	// -소모품 데이터-
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ItemCategory == EItemCategory::Consumable"))
	float HealthToRestore;

	// -업그레이드 데이터-
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ItemCategory == EItemCategory::Upgrade"))
	EUpgradeType UpgradeType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ItemCategory == EItemCategory::Upgrade"))
	float UpgradeValuePerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ItemCategory == EItemCategory::Upgrade"))
	int32 MaxLevel;
};