// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MapLoadingTrigger.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
#include "Components/SphereComponent.h"
#include "Pawn/InventoryPlayer.h"
//sound
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AMapLoadingTrigger::AMapLoadingTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapLoadingTrigger::BeginPlay()
{
	Super::BeginPlay();
	//Get world
	UWorld* World = GetWorld();
	if (nullptr != World)
	{
		//Get Game instance = GI
		UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
		if (GI != nullptr)
		{
			GamesInstance = GI;
			//SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMapLoadingTrigger::HandleTelport);
		}
	}
}

// Called every frame
void AMapLoadingTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void  AMapLoadingTrigger::PlaySound(USoundBase* sound)
{
	if (sound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	}


}

void   AMapLoadingTrigger::HandleTelport(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	
		GamesInstance->SaveAllData();
		PlaySound(ValidSound);
		GamesInstance->LoadMapSafe(MapIndex);
	    Destroy();

	
	
}