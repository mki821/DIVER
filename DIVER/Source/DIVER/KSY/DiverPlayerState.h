#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DiverPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsChanged, int32, NewCoins);
UCLASS()
class DIVER_API ADiverPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ADiverPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Coins")
	void AddCoins(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Coins")
	bool RemoveCoins(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Coins")
	int32 GetCurrentCoins() const;

	UPROPERTY(BlueprintAssignable, Category = "Coins")
	FOnCoinsChanged OnCoinsChanged;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentCoins, VisibleAnywhere, Category = "Coins")
	int32 CurrentCoins;

	UFUNCTION()
	void OnRep_CurrentCoins();
};
