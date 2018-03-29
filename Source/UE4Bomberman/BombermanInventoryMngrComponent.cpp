// Fill out your copyright notice in the Description page of Project Settings.

#include "BombermanInventoryMngrComponent.h"
#include "BombermanPawn.h"
#include "BombActor.h"

#include "Engine.h"

// Sets default values for this component's properties
UBombermanInventoryMngrComponent::UBombermanInventoryMngrComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBombermanInventoryMngrComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBombermanInventoryMngrComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBombermanInventoryMngrComponent::Initialize(ABombermanPawn *setowner)
{
	Owner = setowner;
}


void UBombermanInventoryMngrComponent::PlaceBomb()
{
	if (BombsCount && BombClass) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Owner;
		SpawnInfo.bDeferConstruction = false;
		FTransform bombTransform = FTransform(Owner->GetActorLocation()); // TODO snap bomb position to grid, allow placing only one bomb at grid position (do it through FloorGridActor)

		ABombActor *Bomb = GetWorld()->SpawnActor<ABombActor>(BombClass, bombTransform.GetLocation(), bombTransform.GetRotation().Rotator(), SpawnInfo);
		Bomb->Initialize(this);
		BombsCount--;
	}
}