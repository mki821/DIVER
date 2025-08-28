#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FishData.generated.h"

UCLASS()
class DIVER_API UFishData : public UDataTable
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
