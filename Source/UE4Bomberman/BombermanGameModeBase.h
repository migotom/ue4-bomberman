// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Blueprint/UserWidget.h"
#include "BombermanGameModeBase.generated.h"

class AFloorGridActor;

/**
 * 
 */
UCLASS()
class UE4BOMBERMAN_API ABombermanGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	// Map instance
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FloorGrid)
	AFloorGridActor *Map;

	// Generatge and spawn new grid-map on level
	// @param[in]	FloorGridClass	Class of grid actor used to spawn a map (can be ovverided bluepring with predefined for specific level settings, meshes, materials, etc)
	// @param[in]	mapSizeX			X size of map grid
	// @param[in]	mapSizeY			Y size of map grid
	// @param[in]	seed				Seed used to generate random elements of map (eg. walls placement, pickable items, etc)
	// @param[in]	destructibleWalls	How often put destructible walls into map while generating map content (used by randomized value 0-1)
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SpawnMap(TSubclassOf<AFloorGridActor> FloorGridClass, int mapSizeX = 13, int mapSizeY = 11 , float seed = 78648, float destructibleWalls = 0.75f);
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// GUI Widget class used to present players data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GUI_WidgetClass;

	// Widget instance currently attached to screen
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
