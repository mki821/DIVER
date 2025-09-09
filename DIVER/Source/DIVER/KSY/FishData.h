#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FishData.generated.h"

USTRUCT(BlueprintType)
struct FFishData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName FishID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText FishName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> FishIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SellPrice;
};
