// Fill out your copyright notice in the Description page of Project Settings.

#include "PickableBombs.h"


// Sets default values
APickableBombs::APickableBombs()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
void APickableBombs::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickableBombs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickableBombs::Kill_Implementation()
{
	// TODO add animation

	UE_LOG(LogTemp, Warning, TEXT("APickableBombs::Kill_Implementation()"));
	Destroy();
	return true;
}
