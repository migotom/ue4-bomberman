// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Destroyable_Interface.h"
#include "Pickable_Interface.h"
#include "PickableBombs.generated.h"

class ABombermanPawn;
class UBombermanInventoryMngrComponent;

UCLASS()
class UE4BOMBERMAN_API APickableBombs : public AActor, public IDestroyableInterface, public IPickableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableBombs();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pickable)
	USphereComponent *Collision;

	// Pickable mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pickable)
	UStaticMeshComponent *Mesh;
	
	// How many bombps bomberman will have after picking up this item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Pickable)
	int MaxBombsIncreaseFactor = 3;

	// Animation rotation speed factor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Pickable)
	float AnimRotationSpeed = 60.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Destroy a pickable item on blast
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boom")
	bool Kill();
	virtual bool Kill_Implementation() override;
	
	// Pickup item
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
	bool Pickup(ABombermanPawn *bomberman, UBombermanInventoryMngrComponent *inventorymanager);
	virtual bool Pickup_Implementation(ABombermanPawn *bomberman, UBombermanInventoryMngrComponent *inventorymanager) override;
};
