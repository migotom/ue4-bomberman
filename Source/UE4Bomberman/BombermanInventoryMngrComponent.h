// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BombermanInventoryMngrComponent.generated.h"

class ABombermanPawn;
class ABombActor;
class ABombermanPlayerState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4BOMBERMAN_API UBombermanInventoryMngrComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBombermanInventoryMngrComponent();

	// Class used to spawn bombs (can be a BP with custom mesh, material, etc)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	TSubclassOf<ABombActor> BombClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Owner)
	ABombermanPawn *Owner = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Owner)
	ABombermanPlayerState *PlayerState = nullptr;

	// Maximum number of bombs Bomberman can take
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	int BombsMax = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Initialize actor
	// @param[in]	setowner	Pointer to player's pawn
	// @param[in]	setowner	Pointer to player's state class
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Initialize(ABombermanPawn *setowner, ABombermanPlayerState *setplayerstate);

	// Place bomb at current player position
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PlaceBomb();

	// Add bombs into inventory
	// @param[in]	amount	Amount of bombs to add into inventory
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddBombs(int amount);
};
