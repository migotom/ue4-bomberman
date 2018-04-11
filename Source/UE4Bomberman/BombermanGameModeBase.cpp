// Fill out your copyright notice in the Description page of Project Settings.

#include "BombermanGameModeBase.h"
#include "FloorGridActor.h"

#include "Kismet/GameplayStatics.h"

void ABombermanGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABombermanGameModeBase::SpawnMap(TSubclassOf<AFloorGridActor> FloorGridClass, int mapSizeX, int mapSizeY, float seed, float destructibleWalls)
{
	FTransform mapTransform;

	Map = GetWorld()->SpawnActorDeferred<AFloorGridActor>(FloorGridClass, mapTransform, NULL, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (Map) {
		Map->SizeX = mapSizeX;
		Map->SizeY = mapSizeY;
		Map->Seed = seed;
		Map->DestructibleWallsProbability = destructibleWalls;
		UGameplayStatics::FinishSpawningActor(Map, mapTransform);
	}

}

