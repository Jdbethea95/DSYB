// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseGateActor.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
#include "Components/BoxComponent.h"
#include "Pawn/InventoryPlayer.h"
//sound
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABaseGateActor::ABaseGateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Colider
	BoxComponent = CreateDefaultSubobject< UBoxComponent >(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(FName("Colider"));
	//scale 1.6
	//lock gate
	isLocked = true;
}

// Called when the game starts or when spawned
void ABaseGateActor::BeginPlay()
{
	Super::BeginPlay();
	//Get world
	UWorld* World = GetWorld();
	if (nullptr != World)
	{
		//Get Game instance = GI
		UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
		if (nullptr != GI)
		{
			GamesInstance = GI;
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseGateActor::HandleGateInteraction);
		}
	}
}

// Called every frame
void ABaseGateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void  ABaseGateActor::LockedSound()
{

		PlaySound(InvalidSound);

}

void ABaseGateActor::HandleGateInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Maybe display some UI?
}

void   ABaseGateActor::PlaySound(USoundBase* sound)
{
	if (sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	}

}