#pragma once

#include "BombermanInventoryMngrComponent.h"
#include "BombermanPawn.h"
#include "Pickable_Interface.generated.h"


UINTERFACE(Blueprintable)
class UPickableInterface : public UInterface
{
	GENERATED_BODY()
};

class IPickableInterface
{
	GENERATED_BODY()

public:
	// Pickup pickable item implementation
	// @param[in]	bomberman			Pointer to Player's bomberman pawn
	// @param[in]	inventorymanager	Pointer to Player's inventory manager
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickable Actor")
	bool Pickup(ABombermanPawn *bomberman, UBombermanInventoryMngrComponent *inventorymanager);
};
