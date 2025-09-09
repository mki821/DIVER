#include "KSY/KSYCharacter.h"
#include "Blueprint/UserWidget.h"
#include "KSY/PlayerHUD.h"
#include "ShopWidget.h"

AKSYCharacter::AKSYCharacter()
{
	PlayerHUDClass = nullptr;
	ShopWidgetClass = nullptr;
	PlayerHUDInstance = nullptr;
	ShopWidgetInstance = nullptr;
}

void AKSYCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController && IsLocallyControlled())
	{
		if (PlayerHUDClass)
		{
			PlayerHUDInstance = CreateWidget<UPlayerHUD>(PlayerController, PlayerHUDClass);
			if (PlayerHUDInstance)
			{
				PlayerHUDInstance->AddToViewport();
			}
		}

		if (ShopWidgetClass)
		{
			ShopWidgetInstance = CreateWidget<UShopWidget>(PlayerController, ShopWidgetClass);
		}
	}
}

void AKSYCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("ToggleShop", IE_Pressed, this, &AKSYCharacter::ToggleShop);
}

void AKSYCharacter::ToggleShop()
{
	if (!ShopWidgetInstance) 
		return;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
		return;

	if (ShopWidgetInstance->IsInViewport())
	{
		ShopWidgetInstance->RemoveFromParent();

		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		PlayerController->bShowMouseCursor = false;
	}
	else
	{
		ShopWidgetInstance->AddToViewport();

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(ShopWidgetInstance->TakeWidget());
		PlayerController->SetInputMode(InputMode);

		PlayerController->bShowMouseCursor = true;
	}
}

