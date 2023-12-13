// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageProjectile.generated.h"

UCLASS()
class DONTSPILLYOURBEANS_API ADamageProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Actor Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UProjectileMovementComponent* ProjectileComponent;

	//Actor Stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float lifeSpan;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
		class USoundBase* splat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDropRate(float DropAmount, FVector TargetLocation = FVector(), FVector TargetVelocity = FVector());

private:
	UFUNCTION()
		void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
