// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BossGateActor.h"

//Functionality includes
#include "Utility/MyGameInstance.h"
#include "Pawn/InventoryPlayer.h"
//sound
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
ABossGateActor::ABossGateActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
void ABossGateActor::BeginPlay()
{
	Super::BeginPlay();
	PlaySound(AmbientSound);
}

bool ABossGateActor::CheckBeanCount(int beanCount)
{
	if (beanCount >= BeanAmountToPass)
	{
		PlaySound(ValidSound);
		return true;
	}
	LockedSound();

	return false;
}
void ABossGateActor::HandleGateInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//cast to player
	AInventoryPlayer* player = Cast<AInventoryPlayer>(OtherActor);
	if (player != nullptr)
	{
		if (CheckBeanCount(player->currBeanCount))
		{
			GamesInstance->LoadMapSafe(MapIndex);

		}

	}


}
