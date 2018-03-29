// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Destroyable_Interface.h"
#include "PickableBombs.generated.h"

UCLASS()
class UE4BOMBERMAN_API APickableBombs : public AActor, public IDestroyableInterface
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
	
};
