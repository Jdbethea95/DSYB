// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/MyGameInstance.h"
//Functionality includes
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h" 
//Saving
#include "Utility/SaveFilesSaveGame.h"
#include "Utility/SaveDataSaveGame.h"
#include "Utility/SaveLevelSaveGame.h"
//Player
#include "Pawn/BaseCharacter.h"
#include "Pawn/InventoryPlayer.h"
//loading screen
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
//Level Progression
#include "Utility/ItemManager.h"
#pragma region Functions other
void UMyGameInstance::QuitGame()
{
	//TO DO: pop up are you sure menu
	//and error screen if save failed
	if (CurrentLevelIndex != 0)
	{
		//SaveAllData();
	}

	UWorld* world = GetWorld();
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	if (CurrentLevelIndex != MainMenuIndex)
	{
		SaveAllData();
	}
	UKismetSystemLibrary::QuitGame(world, UGameplayStatics::GetPlayerController(world, 0), QuitPreference, true);

}
#pragma endregion

#pragma region Functions Debug
void UMyGameInstance::ToggleIsDebugTrue()
{
	if (GetisDebugTrue())
	{
		SetisDebugTrue(false);
	}
	else
	{
		SetisDebugTrue(true);
	}
}
bool  UMyGameInstance::GetisDebugTrue()
{
	return isDebugTrue;
}
void UMyGameInstance::SetisDebugTrue(bool input)
{
	isDebugTrue = input;
}
#pragma endregion 
#pragma region Saving and Loading

#pragma region UI 
void UMyGameInstance::ShowLoadingScreen()
{
	//show loading screen
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		//make menu
		UUserWidget* ScreenWidget = CreateWidget<UUserWidget>(PlayerController, LoadingScreenClass);
		//check if worked
		if (ScreenWidget != nullptr)
		{

			LoadingScreenRef = ScreenWidget;
			//add UI to view
			LoadingScreenRef->AddToViewport();
			PlayerController->SetShowMouseCursor(true);
			//Set up input mode
			//input to UI only
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PlayerController->SetInputMode(InputMode);
			LoadingScreenRef->SetIsEnabled(true);
		}

	}
}

void UMyGameInstance::RemoveLoadingScreen()
{

	if (LoadingScreenRef != nullptr)
	{
		//remove parent detroys the loading and doesnt 
		//leave a remaining pointer cause its using the created oading screen
		LoadingScreenRef->RemoveFromParent();
		//show loading screen
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController != nullptr)
		{
			//	PlayerController->EnableInput(PlayerController);
			   //input to UI only
			FInputModeGameOnly InputMode;

			PlayerController->SetInputMode(InputMode);

			LoadingScreenRef->SetIsEnabled(false);
		}
	}

}
void UMyGameInstance::ShowSavingIndicator()
{
	//show loading screen
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		//make menu
		UUserWidget* ScreenWidget = CreateWidget<UUserWidget>(PlayerController, SavingIndicatorClass);
		//check if worked
		if (ScreenWidget != nullptr)
		{
			SavingIndicatorRef = ScreenWidget;
			//add UI to view
			ScreenWidget->AddToViewport();


		}

	}
}
void UMyGameInstance::RemoveSavingIndicator()
{
	if (SavingIndicatorRef != nullptr)
	{
		SavingIndicatorRef->RemoveFromParent();
	}
}

#pragma endregion 
#pragma region Save Info
//call this at game start up so main menu
bool UMyGameInstance::LoadSavesFileData()
{

	if (UGameplayStatics::DoesSaveGameExist("SAVES", 0))
	{
		USaveFilesSaveGame* save = Cast<USaveFilesSaveGame>(UGameplayStatics::LoadGameFromSlot("SAVES", 0));
		if (save != nullptr)
		{
			savingData.savesData = save;
			//saves exist true
			savingData.saveFilesExist = true;
			//check if there is previous player save game to load their data
			int32 index = savingData.savesData->LastActiveSave;
			if (index != -1)
			{
				//their save name index
				savingData.currentSaveIndex = index;
				//their save name
				savingData.currentSaveSlot = savingData.savesData->GetLastActiveSave();

				//double check their save exists 
				if (UGameplayStatics::DoesSaveGameExist(savingData.currentSaveSlot, 0))
				{
					//load their data
					USaveDataSaveGame* playerSave = Cast<USaveDataSaveGame>(UGameplayStatics::LoadGameFromSlot(savingData.currentSaveSlot, 0));
					if (save != nullptr)
					{
						savingData.playerSavedata = playerSave;
					}
				}
			}
		}
		return true;
	}

	//UE_LOG(Game, Error, TEXT("Getting save data failed "));
	return false;


}
bool UMyGameInstance::MakeNewSave(FString SaveSlot)
{

	//check if there is already a save files list
	if (savingData.saveFilesExist && savingData.savesData != nullptr) {
		//Add new save file name to save names data
		if (savingData.savesData->AddSaveFile(SaveSlot))
		{
			//Make new player save data file
			USaveDataSaveGame* playerSD = Cast<USaveDataSaveGame>(UGameplayStatics::CreateSaveGameObject(USaveDataSaveGame::StaticClass()));
			playerSD->saveFileName = SaveSlot;
			savingData.currentSaveSlot = SaveSlot;
			playerSD->playerSaveInfo.mapIndex = HubIndex;
			savingData.playerSavedata = playerSD;
			savingData.currentSaveIndex = savingData.savesData->LastActiveSave;
			//set current index to this

			if (playerSD->Save())
			{
				return true;
			}



		}
		return false;
	}
	else
	{
		//First new save
		USaveFilesSaveGame* newSave = Cast<USaveFilesSaveGame>(UGameplayStatics::CreateSaveGameObject(USaveFilesSaveGame::StaticClass()));
		//set game instance to this one
		savingData.savesData = newSave;
		//make save list
		savingData.savesData->Save();
		//set current save slot name
		savingData.currentSaveSlot = SaveSlot;
		//Add save name
		if (savingData.savesData->AddSaveFile(SaveSlot))
		{
			//saves exist true
			savingData.saveFilesExist = true;

			//Save the new saves data 
			USaveDataSaveGame* playerSD = Cast<USaveDataSaveGame>(UGameplayStatics::CreateSaveGameObject(USaveDataSaveGame::StaticClass()));
			playerSD->saveFileName = SaveSlot;
			savingData.currentSaveSlot = SaveSlot;
			playerSD->playerSaveInfo.mapIndex = 1;
			savingData.playerSavedata = playerSD;
			savingData.currentSaveIndex = savingData.savesData->LastActiveSave;

			if (playerSD->Save())
			{
				return true;
			}


		}

		return false;



	};


}
bool UMyGameInstance::LoadSaveData(FString SaveSlot)
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlot, 0))
	{
		USaveDataSaveGame* save = Cast<USaveDataSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
		if (save != nullptr)
		{
			savingData.currentSaveSlot = SaveSlot;
			savingData.playerSavedata = save;
			return true;
		}
	}
	return false;
}
void UMyGameInstance::LoadCurrentSaveData()
{
	if (savingData.saveFilesExist && savingData.currentSaveSlot != "None")
	{
		LoadSaveData(savingData.currentSaveSlot);

	}
}
bool UMyGameInstance::DeleteSaveData(FString SaveSlot)
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlot, 0))
	{

		FString temp = savingData.playerSavedata->saveFileName;

		//load it to be able to acess sub saves
		USaveDataSaveGame* saveToDelete = Cast<USaveDataSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
		//delete the save
		if (saveToDelete->DeleteSave())
		{
			//remove saves name
			if (savingData.savesData->RemoveSaveFile(SaveSlot))
			{
				//clear if is current active save
				if (temp == SaveSlot)
				{
					ClearSaveInfo();
					LoadMainMenu();

				}
				return true;
			}

		}

	}
	return false;
}
void UMyGameInstance::DeleteCurrentSaveData()
{
	if (savingData.saveFilesExist)
	{
		DeleteSaveData(savingData.currentSaveSlot);

	}
}
bool UMyGameInstance::SaveAllData()
{
	if (savingData.canSaveNow)
	{
		ShowSavingIndicator();
		//cast to player
		AInventoryPlayer* player = Cast<AInventoryPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (player != nullptr)
		{

			if (SavePlayerData(player))
			{

				if (SaveLevelData())
				{
					RemoveSavingIndicator();
					return true;
				}
			
			}
		}
	}
	RemoveSavingIndicator();
	return false;
}
bool UMyGameInstance::SavePlayerData(AInventoryPlayer* player)
{

	//cast to player
	//AInventoryPlayer* player = Cast<AInventoryPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (CurrentLevelIndex != MainMenuIndex)
	{
		if (savingData.playerSavedata != nullptr)
		{

			FArraySlotsContainer playerItems;
			playerItems.AddNewSlot("BN001", player->currBeanCount);
			playerItems.AddNewSlot("BN002", player->currMagicBeanCount);
			playerItems.AddNewSlot("PA001", player->currRedPacketCount);
			playerItems.AddNewSlot("PA002", player->currGreenPacketCount);
			playerItems.AddNewSlot("PA003", player->currGreyPacketCount);
			playerItems.AddNewSlot("PA004", player->currYellowPacketCount);

			savingData.playerSavedata->items.SaveAllItems(playerItems);

			// Health

			savingData.playerSavedata->playerSaveInfo.playerhealth = player->PlayerHealth;
			savingData.playerSavedata->playerSaveInfo.playerMAXhealth = player->PlayerMaxHealth;





			//Stats - passive cost and multplies in passivestateactor 
			//dont need to save jump cost 
			savingData.playerSavedata->playerSaveInfo.HealthCost = player->PassiveStatActor->HealthCost;
			savingData.playerSavedata->playerSaveInfo.DurationCost = player->PassiveStatActor->DurationCost;
			savingData.playerSavedata->playerSaveInfo.CapCost = player->PassiveStatActor->CapacityCost;

			savingData.playerSavedata->playerSaveInfo.CapPassive = player->PassiveStatActor->CapacityCostMultiplier;
			savingData.playerSavedata->playerSaveInfo.HealthPassive = player->PassiveStatActor->MaxHealthPassive;


			//duration
			savingData.playerSavedata->playerSaveInfo.durlevel = player->PassiveStatActor->DurationLevel;

			//caps
			savingData.playerSavedata->playerSaveInfo.caplevel = player->PassiveStatActor->CapacityLevel;
			//passive levels
			savingData.playerSavedata->playerSaveInfo.hplevel = player->PassiveStatActor->HPLevel;

			//multpliers
			savingData.playerSavedata->playerSaveInfo.HPCostMult = player->PassiveStatActor->HealthCostMultiplier;
			savingData.playerSavedata->playerSaveInfo.durcostmult = player->PassiveStatActor->DurationCostMultiplier;
			savingData.playerSavedata->playerSaveInfo.capcostmult = player->PassiveStatActor->CapacityCostMultiplier;
			savingData.playerSavedata->playerSaveInfo.durationpassive = player->PassiveStatActor->DurationCostMultiplier;

			//Bools
			savingData.playerSavedata->playerSaveInfo.CanDoubleJump = player->PassiveStatActor->canDoubleJump;



			if (savingData.playerSavedata->Save())
			{
				return true;
			}

		}
	}

	return false;
}

bool UMyGameInstance::SavePlayerWardrobeData(ABaseCharacter* player)
{
	if (savingData.playerSavedata != nullptr && CurrentLevelIndex == CharMakerMap)
	{
		savingData.playerSavedata->SaveWardrobe(player);
		if (savingData.playerSavedata->Save())
		{
			return true;
		}
	}

	return false;
}

void UMyGameInstance::LoadPlayerWardrobeData(AInventoryPlayer* player)
{
	if (savingData.playerSavedata != nullptr)
	{
		savingData.playerSavedata->LoadWardrobe(player);
	}
}

void UMyGameInstance::DeleteAllSaves()
{
	if (savingData.saveFilesExist)
	{
		if (savingData.savesData->SaveNames.Num() ==1)
		{
			DeleteSaveData(savingData.savesData->SaveNames[0]);
		}
		else 
		{
			if ((savingData.savesData->SaveNames.Num() != 0))
			{
				for (size_t i = 0; i < savingData.savesData->SaveNames.Num(); i++)
				{

					if (UGameplayStatics::DoesSaveGameExist(savingData.savesData->SaveNames[i], 0))
					{

						FString currSave = savingData.playerSavedata->saveFileName;
						FString deletetemp = savingData.savesData->SaveNames[i];
						//load it to be able to acess sub saves
						USaveDataSaveGame* saveToDelete = Cast<USaveDataSaveGame>(UGameplayStatics::LoadGameFromSlot(deletetemp, 0));
						//delete the save
						if (saveToDelete->DeleteSave())
						{
							//remove saves name
							if (savingData.savesData->RemoveSaveFile(deletetemp))
							{
								//clear if is current active save
								if (currSave == deletetemp)
								{
									ClearSaveInfo();
								}

							}

						}

					}

				}

				if (savingData.savesData->SaveNames.Num() == 0)
				{
					LoadMainMenu();

				}

			}
		
		
		}
	}

}

void UMyGameInstance::LoadPlayerSaveData(AInventoryPlayer* player)
{
	if (savingData.playerSavedata != nullptr)
	{
		savingData.playerSavedata->LoadAllItems(player);
		LoadPlayerWardrobeData(player);

#pragma region ABLITY



		//By Default Cost variables have a value, so if a cost == 0, nothing has been saved.
		if (savingData.playerSavedata->playerSaveInfo.DurationCost != 0)
		{
			///////////////////////////
			//STATS AND STUFF 
			///////////////////////////
			player->PlayerHealth = savingData.playerSavedata->playerSaveInfo.playerhealth;
			player->PlayerMaxHealth = savingData.playerSavedata->playerSaveInfo.playerMAXhealth;

#pragma region COSTS

			//////////
			// Costs 
			//////////
		   //player->PassiveStatActor->HealthCost              = savingData.playerSavedata->playerSaveInfo.HealthCost;
		   //player->PassiveStatActor->DurationCost            = savingData.playerSavedata->playerSaveInfo.DurationCost;
		   //player->PassiveStatActor->CapacityCost            = savingData.playerSavedata->playerSaveInfo.CapCost;
		   //player->PassiveStatActor->CapacityCostMultiplier  = savingData.playerSavedata->playerSaveInfo.CapPassive;
			player->LoadShopCosts(savingData.playerSavedata->playerSaveInfo.DurationCost, savingData.playerSavedata->playerSaveInfo.CapCost, savingData.playerSavedata->playerSaveInfo.HealthCost, 200);
#pragma region LEVELS
			//////////////
			// Pasive Levels
			/////////////////////
			player->PassiveStatActor->DurationLevel = savingData.playerSavedata->playerSaveInfo.durlevel;
			player->PassiveStatActor->CapacityLevel = savingData.playerSavedata->playerSaveInfo.caplevel;
			player->PassiveStatActor->HPLevel = savingData.playerSavedata->playerSaveInfo.hplevel;

#pragma endregion
#pragma region MULTIPLIERS
			///////////////
			//COST MULTIPLIERS
			////////////
			player->PassiveStatActor->HealthCostMultiplier = savingData.playerSavedata->playerSaveInfo.HPCostMult;
			player->PassiveStatActor->DurationCostMultiplier = savingData.playerSavedata->playerSaveInfo.durcostmult;
			player->PassiveStatActor->CapacityCostMultiplier = savingData.playerSavedata->playerSaveInfo.capcostmult;

			//-----This is the miss named one
			player->PassiveStatActor->DurationCostMultiplier = savingData.playerSavedata->playerSaveInfo.durationpassive;
#pragma endregion
#pragma region  
			////////////
			// Passives health 
			//////////////
			player->PassiveStatActor->MaxHealthPassive = savingData.playerSavedata->playerSaveInfo.HealthPassive;
			//BOOLS 
			player->PassiveStatActor->canDoubleJump = savingData.playerSavedata->playerSaveInfo.CanDoubleJump;

		}

#pragma endregion

#pragma endregion
	}
}
void UMyGameInstance::ClearSaveInfo()
{
	savingData.currentSaveSlot = "NONE";
	savingData.currentSaveIndex;
	savingData.savesData = nullptr;
	savingData.playerSavedata = nullptr;
	savingData.saveFilesExist = false;

}
bool UMyGameInstance::SaveLevelData()
{
	if (savingData.levelSavedata != nullptr)
	{

		TArray<AActor*> TempActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ItemManager"), TempActors);

		if (!TempActors.IsEmpty())
		{
			itemManager = Cast<AItemManager>(TempActors[0]);
		}

		if (!IsValid(itemManager))
		{
			UE_LOG(LogTemp, Error, TEXT("ITEMMANAGER IS INVALID"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ITEMMANAGER is valid"));
			savingData.levelSavedata->SaveItemStates(itemManager->GetItemStates());
		}

		if (savingData.levelSavedata->Save())
		{
			return true;
		}

	}
	return false;
}
int32 UMyGameInstance::LoadLevelSaveData()
{
	if (savingData.saveFilesExist && savingData.playerSavedata != nullptr)
	{
		FString LevelSaveSlotName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		LevelSaveSlotName = LevelSaveSlotName + savingData.currentSaveSlot;
		//Check if theres a save  and load it
		if (UGameplayStatics::DoesSaveGameExist(LevelSaveSlotName, 0))
		{
			USaveLevelSaveGame* save = Cast<USaveLevelSaveGame>(UGameplayStatics::LoadGameFromSlot(LevelSaveSlotName, 0));
			if (save != nullptr)
			{
				savingData.levelSavedata = save;
				return 0;
			}
		}
		else
		{
			//if none make a new save for it
			USaveLevelSaveGame* save = Cast<USaveLevelSaveGame>(UGameplayStatics::CreateSaveGameObject(USaveLevelSaveGame::StaticClass()));
			if (save != nullptr)
			{
				//name the save
				save->SaveFilesName = LevelSaveSlotName;
				//save it 
				if (UGameplayStatics::SaveGameToSlot(save, LevelSaveSlotName, 0))
				{
					//set it
					savingData.levelSavedata = save;
					//save it as well to the players levels list for deletion later
					savingData.playerSavedata->AddLevelSaveName(LevelSaveSlotName);
					return 1;
				}
			}
		}
	}
	return -1;
}
void UMyGameInstance::LoadGame(int32 saveIndex)
{
	if (savingData.savesData != nullptr && savingData.saveFilesExist)
	{
		savingData.currentSaveIndex = saveIndex;
		savingData.currentSaveSlot = savingData.savesData->SaveNames[saveIndex];
		LoadCurrentSaveData();
		LoadMapHUB();
	}
}
#pragma endregion
#pragma endregion
#pragma region Loading to another Map

void UMyGameInstance::LoadMapTutorial()
{
	LoadMapSafe(TutorialIndex);
}
void UMyGameInstance::LoadMapHUB()
{

	LoadMapSafe(HubIndex);
}
void UMyGameInstance::LoadCharacterMap()
{
	LoadMapSafe(CharMakerMap);
}
void UMyGameInstance::LoadMapFirstLevel()
{

	LoadMapSafe(FirstLevelIndex);
}
void UMyGameInstance::LoadMainMenu()
{

	LoadMapSafe(MainMenuIndex);
}
void UMyGameInstance::LoadCurrentMap()
{

	LoadMapSafe(CurrentLevelIndex);
}
bool UMyGameInstance::CheckIfValidMapIndex(int32 MapIndex)
{
	if (MapIndex > -1 && MapIndex <= Maps.Num())
	{
		return true;
	}
	return false;
}
void UMyGameInstance::LoadMapSafe(int32  MapIndex)
{


	ShowLoadingScreen();
	if (Maps.Num() != 0)
	{
		if (CheckIfValidMapIndex(MapIndex))
		{

			CurrentLevelIndex = MapIndex;
			UGameplayStatics::OpenLevel(GetWorld(), Maps[CurrentLevelIndex]);
			//sucess

		}
		else
		{
			RemoveLoadingScreen();
			//failed
			//UE_LOG(Game, Error, TEXT("Index  : %d is not a valid Map for the GameInstance being used"), MapIndex);
		}


	}
}

#pragma endregion 




