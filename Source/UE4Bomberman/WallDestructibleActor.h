// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Destroyable_Interface.h"
#include "WallDestructibleActor.generated.h"

UCLASS()
class UE4BOMBERMAN_API AWallDestructibleActor : public AActor, public IDestroyableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallDestructibleActor();

	// Wall mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Wall)
	UStaticMeshComponent *Wall;

	//
	// Pickables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Wall)
	TArray<TSubclassOf<AActor>> Pickables;

	// Chance that destruction of wall will spawn loot item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Wall)
	float PickableLootProbability = 0.3f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Destroy a wall
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boom")
	bool Kill();
	virtual bool Kill_Implementation() override;
	
};
