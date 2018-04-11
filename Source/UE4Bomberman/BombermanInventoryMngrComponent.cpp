// Fill out your copyright notice in the Description page of Project Settings.

#include "BombermanInventoryMngrComponent.h"
#include "BombermanPawn.h"
#include "BombermanPlayerState.h"
#include "BombermanGameModeBase.h"
#include "FloorGridActor.h"
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

void UBombermanInventoryMngrComponent::Initialize(ABombermanPawn *setowner, ABombermanPlayerState *setplayerstate)
{
	Owner = setowner;
	PlayerState = setplayerstate;
}


void UBombermanInventoryMngrComponent::PlaceBomb()
{
	const ABombermanGameModeBase *GameMode = Cast<ABombermanGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode && GameMode->Map && PlayerState && PlayerState->BombsCount && BombClass) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Owner;
		SpawnInfo.bDeferConstruction = false;

		// Calculate snapped position of bomb
		FTransform bombTransform = FTransform(Owner->GetActorLocation());
		FVector BombPosition = GameMode->Map->SnapIntoGrid(bombTransform.GetLocation());

		// TODO avoid placing bomb at field where bomb is already

		ABombActor *Bomb = GetWorld()->SpawnActor<ABombActor>(BombClass, BombPosition, bombTransform.GetRotation().Rotator(), SpawnInfo);
		Bomb->Initialize(this, PlayerState);
		PlayerState->BombsCount--;
	}
}

void UBombermanInventoryMngrComponent::AddBombs(int amount)
{
	if (PlayerState) {
		PlayerState->BombsCount+=amount;
	}
}