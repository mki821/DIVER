#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KSYCharacter.generated.h"

class UPlayerHUD;
class UShopWidget;

UCLASS()
class DIVER_API AKSYCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AKSYCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UPlayerHUD> PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UShopWidget> ShopWidgetClass;

private:
	UPROPERTY()
	UPlayerHUD* PlayerHUDInstance;

	UPROPERTY()
	UShopWidget* ShopWidgetInstance;

	void ToggleShop();
};
