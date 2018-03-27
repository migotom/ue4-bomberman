// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorGridActor.h"


// Sets default values
AFloorGridActor::AFloorGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		FTransform xTransform = Transform;
		// Place wall every "IndestrunctibleWallsOffset" step
		for (int i = 0; i < (SizeX - 1) / IndestrunctibleWallsOffset; i++) {
			xTransform.AddToTranslation(xOffset*IndestrunctibleWallsOffset);
			FTransform yTransform = xTransform;

			for (int j = 0; j < (SizeY - 1) / IndestrunctibleWallsOffset; j++) {
				yTransform.AddToTranslation(yOffset*IndestrunctibleWallsOffset);
				Indestrunctible->AddInstanceWorldSpace(yTransform);
				
				// Store information about walls for next steps
				Grid[i][j].SetType(EGridElementType::F_UndestructibleWall);
			}
		}
	}
}

void AFloorGridActor::CleanupInstances()
{
	Floor->ClearInstances();
	Border->ClearInstances();
	Indestrunctible->ClearInstances();
}