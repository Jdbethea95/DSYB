// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/NewSaveMenuWidget.h"

//UI Widgets coded
#include "Interface/ButtonPassStringWidget.h"
//UI BP includes
#include "Components/EditableTextBox.h" 
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#include "Interface/KeyBoardWidget.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
UNewSaveMenuWidget::UNewSaveMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UNewSaveMenuWidget::StaticClass();

}
void  UNewSaveMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Get world
	UWorld* World = GetWorld();
	if (nullptr != World)
	{
		//Get Game instance = GI
		UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
		if (nullptr != GI)
		{
			GamesInstance = GI;
			//Setup 
			BindButtons();
		}
	}

}

void UNewSaveMenuWidget::BindButtons()
{


		buttonConfirm->OnPassAWord.AddDynamic(this, &UNewSaveMenuWidget::NewGame);
		keyboardVirtual->buttonEnter->OnPassAWord.AddDynamic(this, &UNewSaveMenuWidget::ControllerNewGame);
}

void UNewSaveMenuWidget::NewGame(FString SaveName)
{
	if (nullptr != GamesInstance)
	{
		FString SaveNameFromBox = EditableTextBoxInput->GetText().ToString();

		if (GamesInstance->MakeNewSave(SaveNameFromBox))
		{
			GamesInstance->LoadCharacterMap();
		}


	}

}

void UNewSaveMenuWidget::ControllerNewGame(FString SaveName)
{
	if (nullptr != GamesInstance)
	{
		if (SaveName != " ")
		{
			if (GamesInstance->MakeNewSave(SaveName))
			{
				GamesInstance->LoadCharacterMap();
			}
		}


	}
}