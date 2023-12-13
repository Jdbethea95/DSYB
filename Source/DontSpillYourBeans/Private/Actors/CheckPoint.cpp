// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CheckPoint.h"
#include "Sound/SoundBase.h"
#include "Pawn/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMeshComponent"));
	BoxComponent->SetupAttachment(StaticMeshComponent);
	GateMesh->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnCollisionBegin);
	BoxComponent->SetGenerateOverlapEvents(true);
}

void ACheckPoint::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* player = Cast<ABaseCharacter>(OtherActor);

	if (IsValid(player))
	{
		UE_LOG(LogTemp, Warning, TEXT("checkpoint: %d hit"), CheckpointID);
		// Check players previous check point
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GateHitAudio, GetActorLocation());
		OnCheckHit.Broadcast(CheckpointID, player);
	}
}

void ACheckPoint::ToggleGate(bool bIsVisible)
{
	GateMesh->SetVisibility(bIsVisible);
}

