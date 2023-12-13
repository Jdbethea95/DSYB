// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickupObjectShell.h"
#include "Components/BoxComponent.h"
#include "Pawn/InventoryPlayer.h"
#include "Utility/ItemManager.h"
#include "GameFramework/ProjectileMovementComponent.h"
//sound
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
//


// Sets default values
APickupObjectShell::APickupObjectShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Colider
	BoxComponent = CreateDefaultSubobject< UBoxComponent >(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(FName("PickUp"));
	//scale 1.6
	Size = FVector(1.5f, 1.5f, 2.0f);
	BoxComponent->SetWorldScale3D(Size);
}


// Called when the game starts or when spawned
void APickupObjectShell::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupObjectShell::HandlePickUp);

}


// Called every frame
void APickupObjectShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  APickupObjectShell::PlaySound(USoundBase* sound)
{
	UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());

}

void  APickupObjectShell::HandlePickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Cast to player
	AInventoryPlayer* player = Cast<AInventoryPlayer>(OtherActor);

	if (IsValid(player) && IsValid(ItemType))
	{
		//Call base payer function that it is co-ordinated with
		if (player->AddItem(ItemID))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Item added to inventory player: %s"), *ItemID);

			PostPickUp();
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Item not added to inventory player: %s"), *ItemID);

			NoPickUp();
		}
	}
}

void APickupObjectShell::PostPickUp()
{
	if (ValidSound != nullptr)
	{
		PlaySound(ValidSound);
	}
	OnPickUp.Broadcast(ShellId);
	Destroy();
}


void APickupObjectShell::NoPickUp()
{
	if (InvalidSound != nullptr)
	{
		PlaySound(InvalidSound);
	}
}
