// Fill out your copyright notice in the Description page of Project Settings.

#include "BombermanMovementComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UBombermanMovementComponent::UBombermanMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UBombermanMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBombermanMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OwnerMovementComponent) {
		// TODO snaping into grid (in case of optional camera switch to 3rd person like, AddForce methos is mote suitable and natural in 3d)
		// TODO consider replacing this with SetActorLocation to smooth sweep between grid fields (more like traditional 2D version, probably better for mobile)
		OwnerMovementComponent->AddForce(MovementDirection);
		
		// Set mesh rotation 
		OwnerMesh->SetWorldRotation(FMath::RInterpTo(OwnerMesh->GetComponentTransform().Rotator(), DesiredMeshRotation,DeltaTime,20.f));
	}
}

void UBombermanMovementComponent::MoveRight(float val)
{
	if (OwnerMovementComponent) {
		MovementDirection = FVector(val * ForwardForceMultiplier, MovementDirection.Y, 0.f);
		if (val > 0.f)
		{
			DesiredMeshRotation = FRotator(0.f, 0.f, 0.f);
		}
		else if (val < 0.f) {
			DesiredMeshRotation = FRotator(0.f, 180.f, 0.f);
		}
	}
}

void UBombermanMovementComponent::MoveUp(float val)
{
	if (OwnerMovementComponent) {
		MovementDirection = FVector(MovementDirection.X, val * ForwardForceMultiplier, 0.f);
		if (val > 0.f)
		{
			DesiredMeshRotation = FRotator(0.f, 90.f, 0.f);
		}
		else if (val < 0.f) {
			DesiredMeshRotation = FRotator(0.f, -90.f, 0.f);
		}
	}
}


void UBombermanMovementComponent::Initialize(USphereComponent *setcomponent, UStaticMeshComponent *setmesh, AActor *setowner)
{
	OwnerMovementComponent = setcomponent;
	OwnerMesh = setmesh;
	Owner = setowner;
}