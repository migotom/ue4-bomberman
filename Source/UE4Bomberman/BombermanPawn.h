// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Destroyable_Interface.h"
#include "BombermanPawn.generated.h"

class UBombermanMovementComponent;
class UBombermanInventoryMngrComponent;
class ABombermanPlayerState;

UCLASS()
class UE4BOMBERMAN_API ABombermanPawn : public APawn, public IDestroyableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABombermanPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bomberman)
	USphereComponent *Collision = nullptr;

	// Bomberman mesh TODO replace with skeletal mesh / just for test case use static one
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bomberman)
	UStaticMeshComponent *BombermanMesh = nullptr;

	// Bomberman movement and rotation control component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bomberman)
	UBombermanMovementComponent *MovementComponent = nullptr;
	
	// Bomberman simple inventory manager (controls pickups)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bomberman)
	UBombermanInventoryMngrComponent *InventoryManager = nullptr;

	// Player's state class (keeping and replicating all player's important data)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bomberman)
	ABombermanPlayerState *BombermanPlayerState = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Check if Player's Bomberman overlap any of pickable items
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	// Kill player
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boom")
	bool Kill();
	virtual bool Kill_Implementation() override;
};
