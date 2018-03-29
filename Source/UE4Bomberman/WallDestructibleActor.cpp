// Fill out your copyright notice in the Description page of Project Settings.

#include "WallDestructibleActor.h"


// Sets default values
AWallDestructibleActor::AWallDestructibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->SetRootComponent(Wall);
}

// Called when the game starts or when spawned
void AWallDestructibleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallDestructibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWallDestructibleActor::Kill_Implementation()
{
	// TODO add animation
	// animation here

	// Randomize pickable item
	if (FMath::RandRange(0.f, 1.f) > PickableLootProbability && Pickables.Num()) {
		int idx = FMath::RandRange(0, Pickables.Num()-1);
		UE_LOG(LogTemp, Warning, TEXT("Spawning idx %d at pos %s"), idx, *GetActorLocation().ToString());
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = NULL;
		SpawnInfo.Instigator = NULL;
		SpawnInfo.bDeferConstruction = false;
		FTransform itemTransform = FTransform(GetActorLocation());
		itemTransform.AddToTranslation(FVector(0.f, 0.f, 50.f));

		AActor *Item = GetWorld()->SpawnActor<AActor>(Pickables[idx], itemTransform.GetLocation(), itemTransform.GetRotation().Rotator(), SpawnInfo);
	}

	Destroy();
	return true;
}

