// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ActorSpawner.h"
#include "Pawn/BaseCharacter.h"
#include "TimerManager.h"

// Sets default values
AActorSpawner::AActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	//SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AActorSpawner::OnCollisionBegin);
}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnObject();
}

void AActorSpawner::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("spawn collide"));
	ABaseCharacter* player = Cast<ABaseCharacter>(OtherActor);
	if (IsValid(player))
	{
		UE_LOG(LogTemp, Warning, TEXT("Entered Spawning Stage"));
		SpawnObject();
	}
}

void AActorSpawner::PowerUpTaken(AActor* DestroyedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn start"));
	SpawnObject();
}

void AActorSpawner::SpawnObject()
{
	FTimerHandle handler;
	GetWorld()->GetTimerManager().SetTimer(handler, 
		[&]() //Lamda to Spawn Actor after Delay
		{ 
			AActor* powerup = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(), GetActorRotation()); 
			UE_LOG(LogTemp, Warning, TEXT("Spawn end"));

			if (IsValid(powerup))
			{
				powerup->OnDestroyed.AddDynamic(this, &AActorSpawner::PowerUpTaken);
			}
			else 
			{
				PowerUpTaken(nullptr);
			}
		}, 
		DelayTime, false);
}


