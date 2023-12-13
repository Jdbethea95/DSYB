// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TeleportActor.h"
#include "Pawn/BaseCharacter.h"
#include "Actors/PatrolPoint.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATeleportActor::ATeleportActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ATeleportActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeleportActor::OnCollisionBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ATeleportActor::OnCollisionEnd);
	bisUnlocked = false;
}

void ATeleportActor::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<ABaseCharacter>(OtherActor);

	if (bUsePoint)
	{
		if (IsValid(player) && IsValid(TelePoint))
		{
			player->SetActorLocation(TelePoint->GetActorLocation());
		}

		return;
	}

	
	

	if (IsValid(player) && IsValid(OtherTeleportal))
	{
		OnActivate.Broadcast(this, PortalID);
		if (!bJustPorted)
		{
			player->GetCharacterMovement()->Velocity = FVector(0, 0, 0);
			//bJustPorted = true;
	/*		player->SetActorRotation(OtherTeleportal->GetActorRotation());
			player->SetActorLocation(OtherTeleportal->GetActorLocation());*/
		}

	}

}

void ATeleportActor::OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bUsePoint)
	{
		player = nullptr;
		OnDeactivate.Broadcast();
		OtherTeleportal->bJustPorted = false;
	}

}

// Called every frame
void ATeleportActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportActor::SetDestination(ATeleportActor* DestinationPortal)
{
	OtherTeleportal = DestinationPortal;
}

void ATeleportActor::TeleportPlayer()
{
	if (IsValid(player))
	{

		player->SetActorLocation(OtherTeleportal->GetActorLocation());
		//player->SetActorRotation(OtherTeleportal->GetActorRotation());
	}
}

