// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BombermanPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UE4BOMBERMAN_API ABombermanPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:	
	
	// Player's lives
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	int Lives = 5;

	// Current amount of bombs in inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	int BombsCount = 1;

	// Bomb blast radius extension (how far bomb blast is traced)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	int BombBlastExtraRadious = 0;
	
	// Single bomb blast radius
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	float BombBlastRadiousTimer = 0.f;
};
