// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/SaveMenuWidget.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
//#include "Utility/SaveFilesSaveGame.h"
//UI Widgets coded
#include "Interface/ButtonwWithTextWidget.h"
#include "Interface/TextButtonWithIntWidget.h"
//new save menu
#include "Components/EditableTextBox.h" 
#include "Interface/NewSaveMenuWidget.h"
//save slots 
#include "Utility/SaveFilesSaveGame.h"
#include "Components/ScrollBox.h"
#include "Interface/ButtonSaveSlotWidget.h"
//UI BP includes
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

//UI buttons 
#include "Interface/ButtonSaveSlotWidget.h"
#include "Interface/ButtonPassStringWidget.h"
//Functionality includes
#include "Pawn/InventoryPlayer.h"
#include "Kismet/GameplayStatics.h"
USaveMenuWidget::USaveMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = USaveMenuWidget::StaticClass();

}

void  USaveMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	////binding new save menu buttons
	
	UNewSaveMenuWidget* newSM = Cast <UNewSaveMenuWidget>(MenuSwitcher->GetChildAt(1));
	if (newSM != nullptr)
	{
		newSaveMenu = newSM;
		if (GamesInstance->savingData.saveFilesExist && GamesInstance->savingData.savesData->SaveNames.Num() <= 3)
		{
			newSaveMenu->buttonConfirm->OnPassAWord.AddDynamic(this, &USaveMenuWidget::MakeNewSave);
		}
		else
		{
			newSaveMenu->SetIsEnabled(false);
		}
	
	}
	
	if (nullptr != GamesInstance)
	{
		MakeSaveFilesButtons();
	}
	
}


void USaveMenuWidget::BindButtons()
{
	Super::BindButtons();
}
void  USaveMenuWidget::CreateSaveSlotButton(FText name)
{
	// Create the new widget
	UButtonSaveSlotWidget* newSaveSlotWidget  = Cast<UButtonSaveSlotWidget>(CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), SaveSlotButtonClass));

	if (newSaveSlotWidget  != nullptr)
	{
	   //add widget to view
		ScrollBoxSaveSlots->AddChild(newSaveSlotWidget  );

		int32 SlotIndex = ScrollBoxSaveSlots->GetChildIndex(newSaveSlotWidget);
		//widget index also matches save slot index
		newSaveSlotWidget->childIndex = SlotIndex;
		//save file name
		newSaveSlotWidget->SaveSlotName = GamesInstance->savingData.savesData->SaveNames[SlotIndex];
	     //set button text
		newSaveSlotWidget->buttonSaveSlot->buttonTextBlock->SetText(name);

		// bind delete button 
		newSaveSlotWidget->buttonDeleteSave->OnPassNumber.AddDynamic(this, &USaveMenuWidget::DeleteSave);
		newSaveSlotWidget->buttonDeleteSave->number = SlotIndex;
		//Bind overwrite save button
		newSaveSlotWidget->buttonSaveSlot->OnPassNumber.AddDynamic(this, &USaveMenuWidget::OverwriteSave);


	}
	else
	{

	}
}
void USaveMenuWidget::MakeSaveFilesButtons()

{
	if (ScrollBoxSaveSlots->GetChildrenCount() != 0)
	{
		ScrollBoxSaveSlots->ClearChildren();
	}
	if (GamesInstance != nullptr && GamesInstance->savingData.savesData != nullptr)
	{
		if (GamesInstance->savingData.saveFilesExist )
		{
		  for (size_t i = 0; i < GamesInstance->savingData.savesData->SaveNames.Num(); i++)
		  {
		  	CreateSaveSlotButton(FText::FromString((GamesInstance->savingData.savesData->SaveNames[i])));
		  	
		  }
		}
	}

}
void  USaveMenuWidget::MakeNewSave(FString SaveName)
{
	if (nullptr != GamesInstance)
	{
		//FText saveName = newSaveMenu->EditableTextBoxInput->GetText();
		//GamesInstance->savingData.currentSaveSlot = saveName.ToString();

		if (SaveName != "FAILED")
		{
			GamesInstance->savingData.currentSaveSlot = SaveName;


			if (GamesInstance->MakeNewSave(GamesInstance->savingData.currentSaveSlot))
			{
				//UPDATE SAVE FILES MENU
				CreateSaveSlotButton(FText::FromString(SaveName));
				Onsavechange.Broadcast();
			}
		}
		
		CloseMenu();
	}
}
void USaveMenuWidget::RemoveSaveSlot(int32 index)
{
	ScrollBoxSaveSlots->RemoveChildAt(index);
}
void USaveMenuWidget::DeleteSave(int32 index)
{
	//get save slot widg
	UButtonSaveSlotWidget* widget = Cast<UButtonSaveSlotWidget>(ScrollBoxSaveSlots->GetChildAt(index));
	if (widget != nullptr)
	{
		if (GamesInstance->DeleteSaveData(widget->SaveSlotName))
		{

	
				for (size_t i = 0; i < ScrollBoxSaveSlots->GetChildrenCount(); i++)
				{
					ScrollBoxSaveSlots->GetChildAt(i)->RemoveFromParent();
				}

				MakeSaveFilesButtons();
				Onsavechange.Broadcast();
			
		
		}
	
	}
	
}
void USaveMenuWidget::OverwriteSave(int32 index)
{
		GamesInstance->savingData.currentSaveIndex = index;
		GamesInstance->SaveAllData();
		//AInventoryPlayer* player = Cast<AInventoryPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		//if (player != nullptr)
		//{
		//	player->SavePlayerData();
		//	
		//}

}