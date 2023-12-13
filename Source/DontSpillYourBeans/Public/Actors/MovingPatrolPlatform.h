// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPatrolPlatform.generated.h"


class APatrolPoint;

UCLASS()
class DONTSPILLYOURBEANS_API AMovingPatrolPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPatrolPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* StaticMeshComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TArray<APatrolPoint*> Waypoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float PlatformSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float StationaryDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float PointAccuracy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool ReverseNotLoop;

	void PlatformTravel(float DeltaTime);
	void PlatformStationary();
	void UpdateWaypoint();


private:
	int WaypointIndex;
	int IndexLimit;
	float AlphaTime;
	bool IsMoving;
	FVector InitialLocation;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
