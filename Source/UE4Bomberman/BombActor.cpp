// Fill out your copyright notice in the Description page of Project Settings.

#include "BombActor.h"
#include "BombermanInventoryMngrComponent.h"
#include "Engine.h"

// Sets default values
ABombActor::ABombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->SetRootComponent(Mesh);

	// Disable collision for bomb mesh (only blas should have any effect)
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ABombActor::BeginPlay()
{
	Super::BeginPlay();
	BombPlacetAt = FPlatformTime::Seconds();
}

// Called every frame
void ABombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Explode bomb after defined delay
	if (!exloded && FPlatformTime::Seconds() > BombPlacetAt + (double)Timer) {
		Kill();		
	}
}

// Initialize inventory manager
void ABombActor::Initialize(UBombermanInventoryMngrComponent *setinvmanager)
{
	OwnerInventoryManager = setinvmanager;
}

// Explode bomb
bool ABombActor::Kill_Implementation()
{
	if (exloded) {
		return true;
	}
	exloded = true;

	FVector TraceStart = Mesh->GetComponentLocation();

	for (auto Direction : Directions)
	{
		FVector TraceEnd = TraceStart + Direction;
		TArray<FHitResult> HitResults;

		// Trace line from bomb location into one of axis
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f); // Debug
		GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
		for (auto Hit : HitResults) {
			if (Hit.Actor.IsValid()) {
				UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *Hit.Actor->GetName());
				// Check if hit actor implements Destroyable interface (eg. bombs, destroyable walls, pickups, players)
				IDestroyableInterface* DestroyableActor = Cast<IDestroyableInterface>(Hit.Actor.Get());
				if (DestroyableActor) {
					DestroyableActor->Execute_Kill(Hit.Actor.Get()); // initiate kill/destroy sequence for hit actor
				}
			}
		}
	
		// TODO
		// Generace particle effects with explosion animation
	}

	Mesh->DestroyComponent();

	if (OwnerInventoryManager) {
		OwnerInventoryManager->BombsCount++;
	}

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABombActor::OnTimerExpire, DestroyDelay, false);
	
	return true;
}

void ABombActor::OnTimerExpire()
{
	Destroy();
}
