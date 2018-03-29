// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "BombermanMovementComponent.generated.h"


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
	UStaticMeshComponent *OwnerMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Owner)
	float ForwardForceMultiplier = 450000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Owner)
	float RottingForceMultiplier = 2000.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FVector MovementDirection = FVector(0.f,0.f,0.f);
	FRotator DesiredMeshRotation = FRotator(0.f, 0.f, 0.f);
	FRotator CurrentMeshRotation = FRotator(0.f, 0.f, 0.f);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Initialize(USphereComponent *setcomponent, UStaticMeshComponent *setmesh, AActor *setowner);

	// Movement and reotation control methods, initial version, simple physics "add force"
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveUp(float val);

	// Movement and reotation control methods, initial version, simple physics "add force"
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveRight(float val);
};
