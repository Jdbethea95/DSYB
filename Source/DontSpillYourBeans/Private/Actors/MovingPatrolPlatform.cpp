// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MovingPatrolPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/PatrolPoint.h"
#include "TimerManager.h"

// Sets default values
AMovingPatrolPlatform::AMovingPatrolPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WaypointIndex = 0;
	PointAccuracy = 70.0f;
	PlatformSpeed = 0.1f;
	IsMoving = true;
	ReverseNotLoop = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

}

// Called when the game starts or when spawned
void AMovingPatrolPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
	IndexLimit = (Waypoints.Num() - 1);
}

void AMovingPatrolPlatform::PlatformTravel(float DeltaTime)
{
	if (Waypoints.IsEmpty())
	{
		IsMoving = false;
		return;
	}

		float Distance = (GetActorLocation() - Waypoints[WaypointIndex]->GetActorLocation()).Length(); //LOL I had no idea that would work.... neat.
		//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);

		if ( Distance <= PointAccuracy && Waypoints[WaypointIndex]->doDelay)
		{
			PlatformStationary();
		}
		else if (Distance <= PointAccuracy)
		{
			UpdateWaypoint();
		}

		AlphaTime += (DeltaTime * PlatformSpeed);
		FVector Translation = FMath::Lerp(InitialLocation, Waypoints[WaypointIndex]->GetActorLocation(), AlphaTime);

		SetActorLocation(Translation);
	
}

void AMovingPatrolPlatform::PlatformStationary()
{

	FTimerHandle handler;
	IsMoving = false;
	GetWorld()->GetTimerManager().SetTimer(handler, 
		[&]() 
		{
			UpdateWaypoint();
			IsMoving = true;
		},
		StationaryDelay, false);

}

void AMovingPatrolPlatform::UpdateWaypoint()
{
	if (!ReverseNotLoop)
	{

		WaypointIndex++;
		if (WaypointIndex >= Waypoints.Num())
		{
			WaypointIndex = 0;
		}

	}
	else
	{
		if (IndexLimit == 0)
		{
			WaypointIndex--;
			if (WaypointIndex < 0)
			{
				WaypointIndex += 2;
				IndexLimit = (Waypoints.Num() - 1);
			}
		}
		else
		{
			WaypointIndex++;
			if (WaypointIndex >= Waypoints.Num())
			{
				WaypointIndex -= 2;
				IndexLimit = 0;
			}
		}
	}

	AlphaTime = 0;
	InitialLocation = GetActorLocation();
}

// Called every frame
void AMovingPatrolPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsMoving)
	{
		PlatformTravel(DeltaTime);
	}

}

