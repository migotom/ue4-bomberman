// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"

#include "FloorGridActor.generated.h"

class AWallDestructibleActor;

// Map grid definition helper enum (required for randomize fields)
UENUM(BlueprintType)
enum class EGridElementType : uint8
{
	F_Empty				 	UMETA(DisplayName = "Empty field"),
	F_DestructibleWall	 	UMETA(DisplayName = "Destructible wall"),
	F_UndestructibleWall 	UMETA(DisplayName = "Undestructible wall"),
	F_PlayerStart		 	UMETA(DisplayName = "Player start location"),
	F_Enemy				 	UMETA(DisplayName = "Enemy"),
};

// Map grid definition structs (required for randomize fields)
USTRUCT()
struct FGridElement {
	GENERATED_BODY()

public:

	// Type of object placed on field
	EGridElementType ElementType = EGridElementType::F_Empty;

	// Optional, pointer to actor placed on field
	AActor *Element = nullptr;

	inline void SetType(EGridElementType v) { ElementType = v; }
	inline void SetActor(AActor* a) { Element = a; }
};

// Map grid row
USTRUCT()
struct FGridRow {
	GENERATED_BODY()

public:
	FGridRow() {};

	// Constructor initializes array of elements
	FGridRow(int size) {
		GridElement.SetNum(size);
	};

	TArray<FGridElement> GridElement;

	// [] operator for easy access of two dimension grid array
	FGridElement* operator[] (int32 i) {
		return &GridElement[i];
	}
};


//
//
// 

UCLASS()
class UE4BOMBERMAN_API AFloorGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorGridActor();

	// Floor
	//

	// Floor grid instanced meshes 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FloorGrid)
	UInstancedStaticMeshComponent* Floor;

	// Floor plate static mesh (used to fill floor by instanced static mesh comp)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FloorGrid)
	UStaticMesh *FloorPlate;

	// Border
	//

	// Border instanced meshes 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FloorGrid)
	UInstancedStaticMeshComponent* Border;

	// Border box static mesh (used to fill border around floor by instasnced static mesh comp)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FloorGrid)
	UStaticMesh *BorderBox;

	// Inside indestrucntible walls
	//

	// Indestructible walls instanced meshes 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FloorGrid)
	UInstancedStaticMeshComponent* Indestrunctible;

	// Border box static mesh (used to fill border around floor by instasnced static mesh comp)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FloorGrid)
	UStaticMesh *IndestrunctibleBox;

	// Class of destructible wall (can be a BP with custom mesh, material, etc for this level)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FloorGrid)
	TSubclassOf<AWallDestructibleActor> DestructibleWall;

	// Seed for randomize map
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloorGrid, Meta = (ExposeOnSpawn = true))
	int32 Seed = 78648;

	// Probablity of placing destructible grid on floor grid element
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloorGrid, Meta = (ExposeOnSpawn = true))
	float DestructibleWallsProbability = 0.75f;

	// Map size X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloorGrid, Meta = (ExposeOnSpawn = true))
	int SizeX = 13;

	// Map size Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloorGrid, Meta = (ExposeOnSpawn = true))
	int SizeY = 11;

	// Map grid element size (in Unreal units)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloorGrid, Meta = (ExposeOnSpawn = true))
	float Spacing = 100.f;

	// Map floor Z offset (shift plane/walls by this value)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloorGrid, Meta = (ExposeOnSpawn = true))
	float FloorZOffset = 20.f;

	// Spacing between indestructible blocks inside map
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloorGrid, Meta = (ExposeOnSpawn = true))
	float IndestrunctibleWallsOffset = 2;


	//
	//
	// Gamefield grid, required to randomize map content (see construct method)
	UPROPERTY(EditDefaultsOnly, Category = FloorGrid)
	TArray<FGridRow> Grid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Generate floor grid on construct
	virtual void OnConstruction(const FTransform& Transform) override;	

	// Clear instances on editing any property
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;


	// Snap provided position into near grid element
	// @param[in]	Position	Unsnapped position 
	// @return Snapped position
	UFUNCTION(BlueprintCallable, Category = FloorGrid)
	FVector SnapIntoGrid(FVector Position);

private:

	// Cleanup all instanced meshes and grid array
	void CleanupInstances();
};
