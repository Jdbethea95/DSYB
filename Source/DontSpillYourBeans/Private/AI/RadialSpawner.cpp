// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RadialSpawner.h"
#include "Components/SphereComponent.h"
#include "AI/Characters/BaseAICharacter.h"
#include "TimerManager.h"

// Sets default values
ARadialSpawner::ARadialSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RadiusSphere"));
	SphereComponent->SetCollisionProfileName("NoCollision");
	SphereComponent->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void ARadialSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < MaxActiveCount; i++)
	{
		SpawnEnemy();
	}
	
}

void ARadialSpawner::SpawnEnemy()
{
	if (ActiveEnemyCount < MaxActiveCount)
	{
		FActorSpawnParameters Params;
		FVector location = FVector(GetActorLocation().X + FMath::RandRange(-Radius, Radius), 
								   GetActorLocation().Y + FMath::RandRange(-Radius, Radius),
								   GetActorLocation().Z);
		FRotator rotator = GetActorRotation();
		Params.Owner = this;

		AActor* enemyActor = GetWorld()->SpawnActor<AActor>(EnemyType, location, rotator, Params);
		ABaseAICharacter* enemyChar = Cast<ABaseAICharacter>(enemyActor);
		if (IsValid(enemyChar))
		{
			
			enemyChar->OnAIDeath.AddDynamic(this, &ARadialSpawner::AdjustEnemyCount);
			enemyChar->EnemySetup(1, 5, 400, 5);
			enemyChar->SpawnDefaultController();
			AdjustEnemyCount(1);
		}
	}
}

// Called every frame
void ARadialSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARadialSpawner::AdjustEnemyCount(int amount)
{
	ActiveEnemyCount += amount;

	if (amount < 0)
	{
		FTimerHandle TimerHandle;
		//Spawns Enemy after 3-6 seconds
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
			SpawnEnemy();
			}, FMath::RandRange(MinRespawnTime, MaxRespawnTime), false);
	}
}

