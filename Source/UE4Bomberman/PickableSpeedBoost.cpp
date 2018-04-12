// Fill out your copyright notice in the Description page of Project Settings.

#include "PickableSpeedBoost.h"
#include "BombermanPlayerState.h"
#include "Engine.h"

// Sets default values
APickableSpeedBoost::APickableSpeedBoost()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


bool APickableSpeedBoost::Pickup_Implementation(ABombermanPawn *bomberman, UBombermanInventoryMngrComponent *inventorymanager)
{
	UE_LOG(LogTemp, Warning, TEXT("APickableSpeedBoost::Pickup_Implementation()"));
	if (bomberman && bomberman->BombermanPlayerState) {
		bomberman->BombermanPlayerState->SpeedBoost += SpeedIncreaseFactor;
	}

	// TODO picking up animation

	Destroy();
	return true;
}