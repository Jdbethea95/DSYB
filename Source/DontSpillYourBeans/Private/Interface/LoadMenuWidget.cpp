// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/LoadMenuWidget.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
//UI Widgets coded
#include "Interface/ButtonwWithTextWidget.h"
#include "Interface/TextButtonWithIntWidget.h"
//UI BP includes
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
//UI buttons 
#include "Interface/ButtonSaveSlotWidget.h"
//save slots 
#include "Utility/SaveFilesSaveGame.h"
#include "Components/ScrollBox.h"
#include "Interface/ButtonSaveSlotWidget.h"
//
#include "Utility/SaveDataSaveGame.h"

ULoadMenuWidget::ULoadMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = ULoadMenuWidget::StaticClass();

}

void ULoadMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Get world
	UWorld* World = GetWorld();
	if (nullptr != World)
	{
		//Get Game instance = GI
		UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
		if (GI != nullptr)
		{
		
			GamesInstance = GI;
			BindButtons();
		}
		
	}
}



void ULoadMenuWidget::BindButtons()
{
	buttonDeleteAllSaves->buttonWTXT->OnClicked.AddDynamic(this, &ULoadMenuWidget::DeleteAllSaves);

}

void ULoadMenuWidget::MakeLoadButtons()
{

 	if (ScrollBoxSaveSlots->GetChildrenCount() != 0)
 	{
 		ScrollBoxSaveSlots->ClearChildren();
 	}
 	if (GamesInstance != nullptr)
 	{
 		if (GamesInstance->savingData.saveFilesExist)
 		{
 			for (size_t i = 0; i < GamesInstance->savingData.savesData->SaveNames.Num(); i++)
 			{
 				CreateSaveSlotButton(FText::FromString((GamesInstance->savingData.savesData->SaveNames[i])));
 
 			}
			buttonDeleteAllSaves->SetVisibility(ESlateVisibility::Visible);
			return;
 		}
 	}
	buttonDeleteAllSaves->SetVisibility(ESlateVisibility::Hidden);
}

void ULoadMenuWidget::CreateSaveSlotButton(FText name)
{
	// Create the new widget
	UButtonSaveSlotWidget* newSaveSlotWidget = Cast<UButtonSaveSlotWidget>(CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), SaveSlotButtonClass));

	if (newSaveSlotWidget != nullptr)
	{
		//add widget to view
		ScrollBoxSaveSlots->AddChild(newSaveSlotWidget);

		int32 SlotIndex = ScrollBoxSaveSlots->GetChildIndex(newSaveSlotWidget);
		//widget index also matches save slot index
		newSaveSlotWidget->childIndex = SlotIndex;
		//save file name
		newSaveSlotWidget->SaveSlotName = GamesInstance->savingData.savesData->SaveNames[SlotIndex];
		//set button text
		newSaveSlotWidget->buttonSaveSlot->buttonTextBlock->SetText(name);

		// bind delete button 
		newSaveSlotWidget->buttonDeleteSave->OnPassNumber.AddDynamic(this, &ULoadMenuWidget::DeleteSave);
		newSaveSlotWidget->buttonDeleteSave->number = SlotIndex;
		//Bind overwrite save button and use as a load button instead
		newSaveSlotWidget->buttonSaveSlot->OnPassNumber.AddDynamic(GamesInstance, &UMyGameInstance::LoadGame);


	}
	else
	{

	}
}

void ULoadMenuWidget::DeleteSave(int32 index)
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

			MakeLoadButtons();
			OnsaveDeleted.Broadcast();
		}


	}

}

void ULoadMenuWidget::DeleteAllSaves()
{
	GamesInstance->DeleteAllSaves();
	if (ScrollBoxSaveSlots != nullptr)
	{
		ScrollBoxSaveSlots->ClearChildren();
	}

}
