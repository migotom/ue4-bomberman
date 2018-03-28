// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameModeBase.generated.h"

class AFloorGridActor;

/**
 * 
 */
UCLASS()
class UE4BOMBERMAN_API ABombermanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Map instance
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FloorGrid)
	AFloorGridActor *Map;

	// Generatge and spawn new map with defined parameters
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SpawnMap(TSubclassOf<AFloorGridActor> FloorGridClass, int mapSizeX = 13, int mapSizeY = 11 , float seed = 78648, float destructibleWalls = 0.75f);
	
};
