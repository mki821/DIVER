#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class DIVER_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateHP(float NewHP);
	void UpdateOxygen(float NewOxygen);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* OxygenBar;
};
