// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ActorSpawner.generated.h"

UCLASS()
class DONTSPILLYOURBEANS_API AActorSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner");
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner");
	float DelayTime;

	UFUNCTION()
	virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void PowerUpTaken(AActor* DestroyedActor);

private:
	void SpawnObject();

};
