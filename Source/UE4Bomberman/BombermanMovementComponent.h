// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "BombermanMovementComponent.generated.h"

class ABombermanPlayerState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4BOMBERMAN_API UBombermanMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBombermanMovementComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Owner)
	AActor *Owner = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Owner)
	USphereComponent *OwnerMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Owner)
	UStaticMeshComponent *OwnerMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Owner)
	ABombermanPlayerState *PlayerState = nullptr;

	// Value used to calculate physics forward force
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Owner)
	float ForwardForceMultiplier = 450000.f;

	// Value used to calculate physics rotation force
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Owner)
	float RottingForceMultiplier = 2000.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Smoothing movement
	FVector MovementDirection = FVector(0.f,0.f,0.f);
	FRotator DesiredMeshRotation = FRotator(0.f, 0.f, 0.f);

	FRotator CurrentMeshRotation = FRotator(0.f, 0.f, 0.f);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Initialize actor
	// @param[in]	setcomponent	Pointer to pawn's collision sphere
	// @param[in]	setmesh			Pointer to pawn's mesh component
	// @param[in]	setowner		Pointer to pawn itself (owner of movement component)
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Initialize(USphereComponent *setcomponent, UStaticMeshComponent *setmesh, AActor *setowner, ABombermanPlayerState *setplayerstate);

	// Move Bomberman up/down
	// @param[in]	val				Speed of movement -1 ... 1
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveUp(float val);

	// Move Bomberman right/left
	// @param[in]	val				Speed of movement -1 ... 1
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveRight(float val);
};
