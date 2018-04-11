// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorGridActor.h"
#include "WallDestructibleActor.h"
#include "GameFramework/PlayerStart.h"
// Sets default values
AFloorGridActor::AFloorGridActor()
{
	// Playfield will not require to tick
	PrimaryActorTick.bCanEverTick = false;

	// Create instanced static meshes 
	Floor = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FloorPlate"));
	Floor->SetMobility(EComponentMobility::Static);

	Border = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Border"));
	Border->SetMobility(EComponentMobility::Static);

	Indestrunctible = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Indestrunctible walls"));
	Indestrunctible->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void AFloorGridActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorGridActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Cleanup instances (ue4 editor call construnction every content modification)
	CleanupInstances();

	// Prepare offsets
	FVector xOffset(Spacing, 0.f, 0.f);
	FVector yOffset(0.f, Spacing, 0.f);
	FVector zOffset(0.f, 0.f, FloorZOffset);
	FVector spawnOffset(0.f, 0.f, Spacing/2.f);

	//
	// Field data initialization
	Grid.Empty();
	for (int i = 0; i < SizeX; i++) {
		Grid.Add(FGridRow(SizeY));
	}

	//
	// Floor		
	if (FloorPlate) {	
		// Set floor static mesh
		Floor->SetStaticMesh(FloorPlate);
		
		// Fill grid with instances
		FTransform xTransform = Transform;

		xTransform.AddToTranslation(-zOffset);
		for (int i = 0; i < SizeX; i++) {			
			xTransform.AddToTranslation(xOffset);
			FTransform yTransform = xTransform;
			
			for (int j = 0; j < SizeY; j++) {
				yTransform.AddToTranslation(yOffset);
				Floor->AddInstanceWorldSpace(yTransform);
			}
		}
	}

	//
	// Border
	if (BorderBox) {
		// Set wall static mesh
		Border->SetStaticMesh(BorderBox);

		// Fill border with wall instances
		FTransform xUpTransform = Transform;
		FTransform xBottomTransform = Transform;

		// Initial transformations
		xUpTransform.AddToTranslation(-zOffset);
		xUpTransform.AddToTranslation(-xOffset);
		xBottomTransform.AddToTranslation(-xOffset);
		xBottomTransform.AddToTranslation(-zOffset);
		xBottomTransform.AddToTranslation(yOffset* (SizeY + 1 ));

		for (int i = 0; i < SizeX + 2; i++) { 
			xUpTransform.AddToTranslation(xOffset);
			xBottomTransform.AddToTranslation(xOffset);
			Border->AddInstanceWorldSpace(xUpTransform);
			Border->AddInstanceWorldSpace(xBottomTransform);
		}

		// Initial transformations
		FTransform yLeftTransform = Transform;
		FTransform yRightTransform = Transform;
		yRightTransform.AddToTranslation(-zOffset);
		yLeftTransform.AddToTranslation(-zOffset);
		yLeftTransform.AddToTranslation(xOffset * (SizeX + 1));
		for (int i = 0; i < SizeY; i++) {
			yLeftTransform.AddToTranslation(yOffset);
			yRightTransform.AddToTranslation(yOffset);
			Border->AddInstanceWorldSpace(yLeftTransform);
			Border->AddInstanceWorldSpace(yRightTransform);
		}
	}

	//
	// Indestrucntible walls grid
	if (IndestrunctibleBox)
	{
		// Initial grid offset 
		FTransform baseTransform = Transform;
		baseTransform.AddToTranslation(xOffset);
		baseTransform.AddToTranslation(yOffset);

		// Place wall every "IndestrunctibleWallsOffset" step, excluding fields near borders
		for (int i = 1; i < SizeX - 1 ; i+= IndestrunctibleWallsOffset) {
			FTransform xTransform = baseTransform;
			xTransform.AddToTranslation(xOffset*i);

			for (int j = 1; j < SizeY - 1 ; j+= IndestrunctibleWallsOffset) {
				FTransform yTransform = xTransform;
				yTransform.AddToTranslation(yOffset*j);
				Indestrunctible->AddInstanceWorldSpace(yTransform);
				
				// Store information about wall position for next steps
				Grid[i][j]->ElementType = EGridElementType::F_UndestructibleWall;
			}
		}
	}

	FMath::RandInit(Seed);

	//
	// Destructible walls grid
	if (DestructibleWall)
	{
		FTransform xTransform = Transform;
		// Place wall every "IndestrunctibleWallsOffset" step
		for (int i = 0; i < SizeX; i++) {
			xTransform.AddToTranslation(xOffset);
			FTransform yTransform = xTransform;

			for (int j = 0; j < SizeY; j++) {
				yTransform.AddToTranslation(yOffset);
				if ((i == 0 && j == 0) || (i == 0 && j == SizeY-1) || (i == SizeX-1 && j == 0) || (i == SizeX-1 && j == SizeY-1)) {
					// Add player start locations at corners
					FActorSpawnParameters SpawnInfo;
					SpawnInfo.Owner = this;
					SpawnInfo.Instigator = NULL;
					SpawnInfo.bDeferConstruction = false;
					FTransform playerTransform = yTransform; // TODO add correct rotations for j position equals SizeY-1
					playerTransform.AddToTranslation(spawnOffset);
					APlayerStart *Wall = GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), playerTransform.GetLocation(), playerTransform.GetRotation().Rotator(), SpawnInfo);
					
					// Store information about walls for next steps
					Grid[i][j]->ElementType = EGridElementType::F_DestructibleWall;
					Grid[i][j]->Element = Wall;
					continue; 
				}

				if ((i == 0 && (j == 1 || j == SizeY-2)) || (i == 1 && (j == 0 || j == SizeY-1)) || (i == SizeX-2 && (j == 0 || j == SizeY-2)) || (i == SizeX-1 && (j == 1 || j == SizeY-2))) {
					UE_LOG(LogTemp, Warning, TEXT("Skiping placing destructible wall at pos i=%d i=%d"),i,j)
					continue; // Skip fields near players spawn positions to allow them move at least 1 field in two directions
				}

				// Place destructible walls only on empty fields
				if (FMath::RandRange(0.f,1.f) > DestructibleWallsProbability && Grid[i][j]->ElementType == EGridElementType::F_Empty) {
					FActorSpawnParameters SpawnInfo;
					AWallDestructibleActor *Wall = GetWorld()->SpawnActor<AWallDestructibleActor>(DestructibleWall, yTransform.GetLocation(), yTransform.GetRotation().Rotator(), SpawnInfo);

					// Store information about walls for next steps
					Grid[i][j]->ElementType = EGridElementType::F_DestructibleWall;
					Grid[i][j]->Element = Wall;
				}
				
			}
		}
	}
}

// 
// Editor cleanup

void AFloorGridActor::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	CleanupInstances();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AFloorGridActor::CleanupInstances()
{
	Floor->ClearInstances();
	Border->ClearInstances();
	Indestrunctible->ClearInstances();

	// Clear Grid from spawned actors
	for (auto &row : Grid) {
		for (auto &field : row.GridElement) {
			if (field.Element) {
				field.Element->Destroy();
				field.ElementType = EGridElementType::F_Empty;
			}
		}
	}
}


FVector AFloorGridActor::SnapIntoGrid(FVector Position)
{
	FVector RelativePos = Position - GetActorTransform().GetLocation();
	FVector WorldPos = GetActorTransform().GetLocation();

	float X = (FMath::RoundHalfToEven(RelativePos.X / Spacing) * Spacing);
	float Y = (FMath::RoundHalfToEven(RelativePos.Y / Spacing) * Spacing);

	return FVector(WorldPos.X + X, WorldPos.Y + Y, Position.Z);
}