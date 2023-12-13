// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/HubGate.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
#include "Pawn/InventoryPlayer.h"
//sound
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
AHubGate::AHubGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AHubGate::BeginPlay()
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
		
		}
	}
}

// Called every frame
void AHubGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void   AHubGate::HandleGateInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//cast to player
	AInventoryPlayer* player = Cast<AInventoryPlayer>(OtherActor);
	if (player != nullptr)
	{
		if(CheckBeanCount(player->currMagicBeanCount))
		{
			Destroy();
		}
		
	}

}
bool AHubGate::CheckBeanCount(int beanCount)
{
	if (beanCount >= BeanAmountToPass)
	{
		PlaySound(ValidSound);
		return true;
	}
	LockedSound();

	return false;
}
