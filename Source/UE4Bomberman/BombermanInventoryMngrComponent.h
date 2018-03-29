// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BombermanInventoryMngrComponent.generated.h"

class ABombermanPawn;
class ABombActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4BOMBERMAN_API UBombermanInventoryMngrComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBombermanInventoryMngrComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	TSubclassOf<ABombActor> BombClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Owner)
	ABombermanPawn *Owner = nullptr;

	// Maximum number of bombs Bomberman can take
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	int BombsMax = 1;

	// Current amount of bombs in inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	int BombsCount = BombsMax;

	// Single bomb blast radius
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	int BombBlastRadious = 2;

	// Single bomb explosion delay timer
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	float BombTimer = 2.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Initialize(ABombermanPawn *setowner);


	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PlaceBomb();
};
