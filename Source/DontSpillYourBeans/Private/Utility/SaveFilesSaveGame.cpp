// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/SaveFilesSaveGame.h"
//Functionality includes 
#include "Kismet/GameplayStatics.h"
USaveFilesSaveGame::USaveFilesSaveGame()
{
	SaveFilesName = "SAVES";
	LastActiveSave = -1;
}

bool  USaveFilesSaveGame::Save()
{
	if(UGameplayStatics::SaveGameToSlot(this, SaveFilesName, 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}
USaveFilesSaveGame* USaveFilesSaveGame::LoadSavesFileData()
{
	if (CheckifSaveExists())
	{
		USaveFilesSaveGame* save = Cast<USaveFilesSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveFilesName, 0));
		if (save != nullptr)
		{
			return save;
		}
	}
	return nullptr;
}
bool USaveFilesSaveGame::CheckifSaveExists()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveFilesName, 0))
	{
		//UE_LOG(Game, Display, TEXT(" %s : exists "), *SaveFilesName);
		return true;
	}

		//	UE_LOG(Game, Display, TEXT(" %s : doesnt exist "), *SaveSlot);
		return false;


}

int32  USaveFilesSaveGame::GetSaveIndex(FString SaveToGet)
{
	//return - 1 if failed
	return SaveNames.IndexOfByKey(SaveToGet);
}
bool USaveFilesSaveGame::RemoveSaveFile(FString SaveToRemove)
{
	if(CheckifSaveExists())
	{
		int32 index = GetSaveIndex(SaveToRemove);
		if (index == -1)
		{
			//Invalid index
			return false;
		}
		else
		{

			//UE_LOG(Game, Display, TEXT("%s index : %d   "), *SaveIndexToRemove, index)
					//If Save array is empty delete this save File as well
			if (SaveNames.Num() == 1 && index == 0)
			{
				//delete the save
				if (UGameplayStatics::DeleteGameInSlot(SaveToRemove, 0))
				{

				}
				
				//UE_LOG(Game, Display, TEXT(" Deleting save files list because its empty"));
				UGameplayStatics::DeleteGameInSlot(SaveFilesName, 0);
	
				return true;
			}
			//////////////////////////
			// NOt empty 
			/////////////////////

			//delete the save
			if (UGameplayStatics::DeleteGameInSlot(SaveToRemove, 0))
			{

			}
			//Removing the save file
			SaveNames.RemoveAt(index);

			//last index was deleted
			if (index == LastActiveSave)
			{
				LastActiveSave = 0-1;
			}
			//UE_LOG(Game, Display, TEXT("Removed from save files list : % s index : % d   "), *CurrentSaveSlot, index);
			Save();
			return true;
		}

	}

		//Save File deosnt exist
		return false;

}

bool USaveFilesSaveGame::AddSaveFile(FString  SaveSlotToAdd)
{
	if(CheckifSaveExists())
	{
	
	//add current slot to array
	//UE_LOG(Game, Display, TEXT("adding save name to save file to : %s"), *SaveFilesName);
	SaveNames.Add(SaveSlotToAdd);
	//set last save to the new save file
	LastActiveSave = SaveNames.Num() - 1;
	//Save
	UGameplayStatics::SaveGameToSlot(this, SaveFilesName, 0);
	return true;
	}


	//	UE_LOG(Game, Display, TEXT(" %s : Failed to add save file "), *SaveSlot);
		return false;


}

FString USaveFilesSaveGame::GetLastActiveSave()
{
	
	return SaveNames[LastActiveSave];
	
}