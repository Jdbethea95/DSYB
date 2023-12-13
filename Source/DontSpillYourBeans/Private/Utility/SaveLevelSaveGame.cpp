// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/SaveLevelSaveGame.h"
//Functionality includes 
#include "Kismet/GameplayStatics.h"
USaveLevelSaveGame::USaveLevelSaveGame()
{
}

void USaveLevelSaveGame::DestroyLoadedPickups()
{

	for (AActor* actor : actorsToDestroy)
	{
			actor->Destroy();
    }
	
}
void USaveLevelSaveGame::AddDestroyed(AActor* destroyed)
{

	actorsToDestroy.AddUnique(destroyed);
}

TArray<int> USaveLevelSaveGame::LoadItemStates()
{
	return CollectedListOfItems;
}

void USaveLevelSaveGame::SaveItemStates(TArray<int> ListOfItems)
{
	if (UGameplayStatics::DoesSaveGameExist(SaveFilesName, 0))
	{
		CollectedListOfItems = ListOfItems;
	}
}

bool USaveLevelSaveGame::Save()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveFilesName, 0))
	{
		if (UGameplayStatics::SaveGameToSlot(this, SaveFilesName, 0))
		{
			return true;
		}

	}
	return false;
}
