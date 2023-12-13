// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RadialSpawner.generated.h"

UCLASS()
class DONTSPILLYOURBEANS_API ARadialSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARadialSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* SphereComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Class Reference")
		TSubclassOf<class ABaseAICharacter> EnemyType;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variable|Stats")
		int MaxActiveCount;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variable|Stats")
		int Radius;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variable|Stats")
		float MinRespawnTime;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variable|Stats")
		float MaxRespawnTime;

	void SpawnEnemy();

	int ActiveEnemyCount;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// increments the total enemies active
	/// 
	/// </summary>
	/// <param name="amount"></param>
	UFUNCTION()
	void AdjustEnemyCount(int amount);
};
