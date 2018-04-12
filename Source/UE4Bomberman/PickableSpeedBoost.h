// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableActor.h"
#include "Components/SphereComponent.h"
#include "Destroyable_Interface.h"
#include "Pickable_Interface.h"

#include "PickableSpeedBoost.generated.h"

class ABombermanPawn;
class UBombermanInventoryMngrComponent;

UCLASS()
class UE4BOMBERMAN_API APickableSpeedBoost : public APickableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableSpeedBoost();

	// How many bombps bomberman will have after picking up this item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Pickable)
	float SpeedIncreaseFactor = 0.1f;

protected:

public:	

	// Pickup this bombs into Player's inventory
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
	bool Pickup(ABombermanPawn *bomberman, UBombermanInventoryMngrComponent *inventorymanager);
	virtual bool Pickup_Implementation(ABombermanPawn *bomberman, UBombermanInventoryMngrComponent *inventorymanager) override;
};
