// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Destroyable_Interface.h"
#include "BombActor.generated.h"

class UBombermanInventoryMngrComponent;

UCLASS()
class UE4BOMBERMAN_API ABombActor : public AActor, public IDestroyableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bomb)
	UStaticMeshComponent *Mesh;

	// This bomb blast radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bomb, Meta = (ExposeOnSpawn = true))
	float BlastRadious = 300;

	// This bomb explosion delay timer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bomb, Meta = (ExposeOnSpawn = true))
	float Timer = 2.f;

	// List of explosion vectors
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bomb)
	TArray<FVector> Directions = { FVector(0,BlastRadious,0), FVector(BlastRadious,0,0), FVector(0,-BlastRadious,0), FVector(-BlastRadious,0,0) };


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bomb)
	UBombermanInventoryMngrComponent *OwnerInventoryManager = nullptr;

	// Mark bomb as already exploded
	bool exloded = false;

	// Delay of actor destruction (to finish particle animations)
	float DestroyDelay = 0.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Timestamp of bomb placement
	double BombPlacetAt = 0.0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Destroy actor on expire timer event
	void OnTimerExpire();
		
	UFUNCTION(BlueprintCallable, Category = "Boom")
	void Initialize(UBombermanInventoryMngrComponent *setinvmanager);

	// Explode bomb (as interface to allow chain-reaction)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boom")
	bool Kill();
	virtual bool Kill_Implementation() override;
};
