// Fill out your copyright notice in the Description page of Project Settings.

#include "PickableActor.h"


// Sets default values
APickableActor::APickableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere collision"));
	Collision->SetSphereRadius(49.5f);

	// Set collision and constraints for movement
	this->SetRootComponent(Collision);

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Simple rotation animation
	Mesh->AddLocalRotation(FRotator(0.f, AnimRotationSpeed * DeltaTime, 0.f));
}

bool APickableActor::Kill_Implementation()
{
	// TODO add animation

	UE_LOG(LogTemp, Warning, TEXT("APickableActor::Kill_Implementation()"));
	Destroy();
	return true;
}


bool APickableActor::Pickup_Implementation(ABombermanPawn *bomberman, UBombermanInventoryMngrComponent *inventorymanager)
{
	return true;
}