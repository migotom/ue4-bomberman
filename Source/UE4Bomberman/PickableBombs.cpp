// Fill out your copyright notice in the Description page of Project Settings.

#include "PickableBombs.h"
#include "BombermanInventoryMngrComponent.h"
#include "BombermanPawn.h"
#include "Engine.h"

// Sets default values
APickableBombs::APickableBombs()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}





bool APickableBombs::Pickup_Implementation(ABombermanPawn *bomberman, UBombermanInventoryMngrComponent *inventorymanager)
{
	UE_LOG(LogTemp, Warning, TEXT("APickableBombs::Pickup_Implementation()"));
	if (inventorymanager) {
		inventorymanager->BombsMax += 3;
		inventorymanager->AddBombs(3);
	}
	
	// TODO picking up animation

	Destroy();
	return true;
}