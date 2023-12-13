// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/ItemManager.h"
#include "Actors/PickupObjectShell.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItemManager::AItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	IsShellSet = false;

}

// Called when the game starts or when spawned
void AItemManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsShellSet)
	{
		SetUpPickShells();
	}



}

// Called every frame
void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



TArray<int> AItemManager::GetItemStates()
{
	return CollectedList;
}

void AItemManager::SetItemStates(TArray<int> UpdatedList)
{
	if (!IsShellSet)
	{
		SetUpPickShells();
	}

	CollectedList = UpdatedList;

	if (!pickupList.IsEmpty())
	{
		for (size_t i = 0; i < CollectedList.Num(); i++)
		{
			pickupList[CollectedList[i]]->Destroy();
		}
	}
}


void AItemManager::UpdateCollectedList(int pickupID)
{
	if (!CollectedList.Contains(pickupID))
	{
		UE_LOG(LogTemp, Error, TEXT("Collection saved"));
		CollectedList.Add(pickupID);
	}
}

void AItemManager::SetUpPickShells()
{
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Pickup"), ActorList);

	for (size_t i = 0; i < ActorList.Num(); i++)
	{
		APickupObjectShell* ShellTemp = Cast<APickupObjectShell>(ActorList[i]);
		if (IsValid(ShellTemp))
		{
			pickupList.Add(ShellTemp);
		}
	}

	for (size_t i = 0; i < pickupList.Num(); i++)
	{
		pickupList[i]->ShellId = i;
		pickupList[i]->OnPickUp.AddDynamic(this, &AItemManager::UpdateCollectedList);
	}
	IsShellSet = true;
}

void AItemManager::CheckInShell(APickupObjectShell* object)
{
	if (IsValid(object))
	{
		object->ShellId = IDIncrement;
		object->OnPickUp.AddDynamic(this, &AItemManager::UpdateCollectedList);
		IDIncrement++;
		pickupList.Add(object);
	}
}

