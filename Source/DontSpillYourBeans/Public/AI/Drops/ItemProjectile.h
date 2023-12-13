// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemProjectile.generated.h"

class APickupObjectShell;

UCLASS()
class DONTSPILLYOURBEANS_API AItemProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemProjectile();

	bool ShootItem(FVector OwnerLocation, FVector OwnerVelocity);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		TArray<TSubclassOf<APickupObjectShell>> Items;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UProjectileMovementComponent* ProjectileComponent;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MinDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float lifeSpan;

	UFUNCTION()
		void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool hasSpawned;

};
