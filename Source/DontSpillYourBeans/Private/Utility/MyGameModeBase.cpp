// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/MyGameModeBase.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
//Save includes
#include "Utility/SaveLevelSaveGame.h"
//UI
#include "Blueprint/UserWidget.h"
//Player
#include "Pawn/InventoryPlayer.h"
#include "Interface/DefeatWidget.h"
#include "Components/Button.h"
//Level Progression
#include "Utility/ItemManager.h"
AMyGameModeBase::AMyGameModeBase()
{

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
// Called when the game starts or when spawned
void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (nullptr != GamesInstance)
	{

		GamesInstance->ShowLoadingScreen();

		SetUpPlayerDefeat();
	
		//find all actors of the class
	    //LOADING/SETUP
		// load level save data
		if (LoadLevelSaveData() == 0)
		{
			TArray<AActor*> TempActors;
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ItemManager"), TempActors);

			if (!TempActors.IsEmpty())
			{
				itemManager = Cast<AItemManager>(TempActors[0]);
			}

			if (IsValid(itemManager))
			{
				GamesInstance->itemManager = itemManager;
				itemManager->SetItemStates(GamesInstance->savingData.levelSavedata->LoadItemStates());
			}

			if (!IsValid(itemManager))
			{
				UE_LOG(LogTemp, Error, TEXT("ITEMMANAGER IS INVALID"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("ITEMMANAGER is valid"));
			}

			// Destroy all actors that need to be
			//DestroyLoadedActors();
		}
		// Bind all remaining destroyable actors
		//BindAllDestroyable();


	
		//set input back to game only 
		//delay a bit for enviroment loading
		//remove loading screen
		GamesInstance->RemoveLoadingScreen();
	}
}



#pragma region DEFEAT
void AMyGameModeBase::ShowDefeatScreen()
{

}

void AMyGameModeBase::RemoveDefeatScreen()
{
	if (DefeatScreenRef != nullptr)
	{
		DefeatScreenRef->RemoveFromParent();
	}

}
void AMyGameModeBase::Defeated()
{
	ShowDefeatScreen();
}

void AMyGameModeBase::RespawnPlayer()
{
	AInventoryPlayer* player = Cast<AInventoryPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (player != nullptr)
	{
		if (IsValid(PlayerDefeatWidget))
		{
			player->PlayerReset();
			PlayerDefeatWidget->HideDefeatScreen();
		}
	}
}
#pragma endregion 
#pragma region SAVING/LOADING
	
int32 AMyGameModeBase::LoadLevelSaveData()
{

	if (nullptr != GamesInstance)
	{
		int32 res  = GamesInstance->LoadLevelSaveData();
		return res;
	}
	// this is just to return something isnt actually an error
	return -1;
}


void AMyGameModeBase::BindDestroyed(TSubclassOf<class AActor > ActorClass)
{
	//find all actors of the class
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, FoundActors);
	//if not empty ->
	if (FoundActors.Num() > 0)
	{
		if (LevelData != nullptr)
			//Bind their on destroy to the add them to the level save array
			for (AActor* actor : FoundActors)
			{
				if (actor != nullptr)
				{
					actor->OnDestroyed.AddDynamic(LevelData, &USaveLevelSaveGame::AddDestroyed);
				}
			}
	}
	
}
void AMyGameModeBase::BindAllDestroyable()
{
	for (TSubclassOf<class AActor > actor : ActorClassesToSaveDestruction)
	{
		BindDestroyed(actor);
	}
}
void AMyGameModeBase::DestroyLoadedActors()
{
	if (LevelData != nullptr)
	{
		LevelData->DestroyLoadedPickups();
	}
}
void AMyGameModeBase::SetUpPlayerDefeat()
{


	//freeze player movement
	//display loading screen
	//GamesInstance->ShowLoadingScreen();
	//Bind Player Death
	AInventoryPlayer* player = Cast<AInventoryPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Made It In player"));
		//Setting up Defeat Widget
		APlayerController* PlayerController = Cast<APlayerController>(player->GetController());
		if (PlayerController != nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Made It In controller"));
			//make menu
			PlayerDefeatWidget = CreateWidget<UDefeatWidget>(PlayerController, DeafeatScreenClass);
			//check if worked
			if (PlayerDefeatWidget != nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Made It In Widget"));
				//add UI to view
				PlayerDefeatWidget->AddToViewport();
				PlayerDefeatWidget->HideDefeatScreen();

				player->OnDeath.AddDynamic(PlayerDefeatWidget, &UDefeatWidget::ShowDefeatScreen);
				PlayerDefeatWidget->RespawnButton->OnClicked.AddDynamic(this, &AMyGameModeBase::RespawnPlayer);

				PlayerDefeatWidget->MainMenuButton->OnClicked.AddDynamic(PlayerDefeatWidget, &UDefeatWidget::HideDefeatScreen);
				PlayerDefeatWidget->MainMenuButton->OnClicked.AddDynamic(GamesInstance, &UMyGameInstance::LoadMainMenu);
			}

		}
	}
}
#pragma endregion 