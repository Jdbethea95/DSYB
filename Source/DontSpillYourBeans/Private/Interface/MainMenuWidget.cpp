// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/MainMenuWidget.h"
//UI Widgets coded
#include "Interface/ButtonwWithTextWidget.h"
#include "Interface/TextButtonWithIntWidget.h"
#include "Interface/ButtonPassStringWidget.h"
//Loading
#include "Interface/LoadMenuWidget.h"
//UI BP includes
#include "Components/EditableTextBox.h" 
//Functionality includes
#include "Utility/MyGameInstance.h"
#include "Utility/SaveDataSaveGame.h"
#include "Utility/SaveFilesSaveGame.h"
//UI BP includes
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
//Functionality includes
#include "Kismet/GameplayStatics.h"
UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UMainMenuWidget::StaticClass();

}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ToggleLoadMenuUI();
}
void UMainMenuWidget::BindButtons()
{
	Super::BindButtons();
	if (GamesInstance != nullptr)
	{
		
		if (!GamesInstance->savingData.saveFilesExist)
		{
			//load save files and automatically load last save
			GamesInstance->LoadSavesFileData();
		}
		//bind quit
		buttonQuit->buttonWTXT->OnClicked.AddDynamic(GamesInstance, &UMyGameInstance::QuitGame);
	
		//load menu save slot buttons update
		ULoadMenuWidget* Loadwidget = Cast <ULoadMenuWidget >(MenuSwitcher->GetWidgetAtIndex(2));
		if (Loadwidget !=nullptr)
		{
			Loadwidget->OnsaveDeleted.AddDynamic(this, &UMainMenuWidget::ToggleLoadMenuUI);
			Loadwidget->MakeLoadButtons();
			
		}

	}



}

void UMainMenuWidget::ToggleLoadMenuUI()
{
	if (GamesInstance != nullptr)
	{

		//this check is so if you are back to main menu while in game
		if (!GamesInstance->savingData.saveFilesExist)
		{
			//disable continue
			buttonplay->SetVisibility(ESlateVisibility::Hidden);
			//disable load button
			tabButtons->GetChildAt(LoadButtonIndex)->SetIsEnabled(false);
			buttonNewGame->SetIsEnabled(true);
		
		}
		else
		{
			if (GamesInstance->savingData.playerSavedata != nullptr)
			{

				//enable continue
				buttonplay->SetVisibility(ESlateVisibility::Visible);
				//get map index for button
				buttonplay->number = GamesInstance->HubIndex;
				//GamesInstance->savingData.playerSavedata->playerSaveInfo.mapIndex;
				//play button binding loading to level
				buttonplay->OnPassNumber.AddDynamic(GamesInstance, &UMyGameInstance::LoadMapSafe);
				//load menus buttons
				ULoadMenuWidget* loadMenu = Cast <ULoadMenuWidget >(MenuSwitcher->GetWidgetAtIndex(1));
				if (loadMenu != nullptr)
				{
					loadMenu->MakeLoadButtons();
				}
		
			}
			//limit amount of saves to 3
			if (GamesInstance->savingData.savesData->SaveNames.Num() < GamesInstance->saveLimit)
			{
				buttonNewGame->SetIsEnabled(true);
			}
			else
			{
				buttonNewGame->SetIsEnabled(false);
			
			}
			
			
		}
	}
	
	SetNextFocus();

}

