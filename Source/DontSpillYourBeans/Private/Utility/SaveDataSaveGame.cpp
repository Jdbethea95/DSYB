// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/SaveDataSaveGame.h"
//Functionality includes 
#include "Kismet/GameplayStatics.h"
#include "Pawn/InventoryPlayer.h"
#include "Pawn/BaseCharacter.h"
USaveDataSaveGame::USaveDataSaveGame()
{
	saveFileName = "None";


}

bool USaveDataSaveGame::CheckifSaveExists()
{
	if (UGameplayStatics::DoesSaveGameExist(saveFileName, 0) && saveFileName != "None")
	{
		//UE_LOG(Game, Display, TEXT(" %s : exists "), *SaveFilesName);
		return true;
	}
	else
	{
		//	UE_LOG(Game, Display, TEXT(" %s : doesnt exist "), *SaveSlot);
		return false;
	}

}

bool USaveDataSaveGame::Save()
{
	if (UGameplayStatics::SaveGameToSlot(this, saveFileName, 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void USaveDataSaveGame::AddLevelSaveName(FString LevelSaveSlotName)
{
	LevelSaveNames.Add(LevelSaveSlotName);
	//sav
	Save();
}

bool USaveDataSaveGame::DeleteSave()
{
	bool deleted = false;
	int numSubSaveFileCount = LevelSaveNames.Num();
	int DeletedCount = 0;
	//check valid save
	if (CheckifSaveExists())
	{
		//has sub saves
		if (LevelSaveNames.Num() != 0)
		{
			//delete sub saves
			for (size_t i = 0; i < LevelSaveNames.Num(); i++)
			{
				//check if valid
				if (UGameplayStatics::DoesSaveGameExist(LevelSaveNames[i], 0))
				{
					//delete it
					if (UGameplayStatics::DeleteGameInSlot(LevelSaveNames[i], 0))
					{
						DeletedCount++;
					}

				}
			}
		}
		//delete the players save file

		   	return UGameplayStatics::DeleteGameInSlot(saveFileName, 0);
		
		
	}
	return false;
}

void USaveDataSaveGame::SaveAllAblities(TArray<int>& costs, TArray<int>& durrationsInts, TArray<int>& durrationsFloats, TArray<float>& multiplier, TArray<bool>& bools)
{
	////Costs
	//for (size_t i = 0; i < costs.Num(); i++)
	//{
	//	//set var
	//	if (!playerAblity.ablityCosts.SetSlot(i, costs[i]))
	//	{
	//		//if doesnt exist yet in save add it
	//		playerAblity.ablityCosts.AddNewSlot(costs[i]);
	//	}
	//
	//}
	//
	
	//durations ints
	//for (size_t i = 0; i < durrationsInts.Num(); i++)
	//{
	//	//set var
	//	if (!playerAblity.passiveInts.SetSlot(i, durrationsInts[i]))
	//	{
	//		//if doesnt exist yet in save add it
	//		playerAblity.passiveInts.AddNewSlot(durrationsInts[i]);
	//	}
	//
	//}
	////durations floats
	//for (size_t i = 0; i < durrationsFloats.Num(); i++)
	//{
	//	//set var
	//	if (!playerAblity.passiveFloats.SetSlot(i, durrationsFloats[i]))
	//	{
	//		//if doesnt exist yet in save add it
	//		playerAblity.passiveFloats.AddNewSlot(durrationsFloats[i]);
	//	}
	//
	//}
	//
	//
	////multiplers
	//for (size_t i = 0; i < multiplier.Num(); i++)
	//{
	//	//set var
	//	if (!playerAblity.ablityCostMultipliers.SetSlot(i, multiplier[i]))
	//	{
	//		//if doesnt exist yet in save add it
	//		playerAblity.ablityCostMultipliers.AddNewSlot(multiplier[i]);
	//	}
	//
	//}
	////bools
	//for (size_t i = 0; i < bools.Num(); i++)
	//{
	//	//set var
	//	if (!playerAblity.ablityBools.SetSlot(i, bools[i]))
	//	{
	//		//if doesnt exist yet in save add it
	//		playerAblity.ablityBools.AddNewSlot(bools[i]);
	//	}
	//
	//}
}

void USaveDataSaveGame::SaveAllItems(FArraySlotsContainer& inventory)
{
	UE_LOG(LogTemp, Warning, TEXT("SaveAllItems Count:   %f "), inventory.Count());
	items.SaveAllItems(inventory);

}

void USaveDataSaveGame::LoadAllItems(AInventoryPlayer* Player)
{
	for (size_t i = 0; i < items.Count(); i++)
	{
		
			if (items.GetSlotsAmount(i) != 0)
			{
				Player->AddItem(items.GetSlotNameID(i), items.GetSlotsAmount(i));
			}
		


	}
}

void USaveDataSaveGame::SaveWardrobe(ABaseCharacter* Player)
{
	if (Player != nullptr)
	{
		playerSaveInfo.emotionIndex = Player->EmoIndex;
		playerSaveInfo.skinIndex = Player->SkinIndex;
	}

}

void USaveDataSaveGame::LoadWardrobe(AInventoryPlayer* Player)
{
	if (Player != nullptr)
	{
		Player->EmoIndex = playerSaveInfo.emotionIndex;
		Player->SkinIndex = playerSaveInfo.skinIndex;
	}
}





