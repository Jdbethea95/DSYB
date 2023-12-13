// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/DebugMenuWidget.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
//UI BP includes
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
//UI Widgets coded
#include "Interface/ButtonwWithTextWidget.h"
#pragma region Construction
UDebugMenuWidget::UDebugMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UDebugMenuWidget::StaticClass();

}

void UDebugMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//bind toggle buttton 
	// //TO do move to bind func
	ToggleDebug();
	buttonDebug->buttonWTXT->OnClicked.AddDynamic(this, &UDebugMenuWidget::ToggleDebug);
	
	if (buttonClose != nullptr && GamesInstance->CurrentLevelIndex == 0)
	{
		//disable buttons in main menu
		for (size_t i = 0; i < 3; i++)
		{
			//stats,beans,spawn
			tabButtons->GetChildAt(i)->SetIsEnabled(false);
		}

		buttonClose->SetVisibility(ESlateVisibility::Hidden);
	}
	

}


#pragma endregion 

#pragma region Button functionality

void  UDebugMenuWidget::ToggleDebug()
{
	if (GamesInstance->GetisDebugTrue())
	{
		GamesInstance->ToggleIsDebugTrue();
		//SetDebug Buttons Text
		buttonDebug->buttonTextBlock->SetText(FText::FromString("Debug : False"));
	
	}
	else
	{
		GamesInstance->ToggleIsDebugTrue();
		//SetDebug Buttons Text
		buttonDebug->buttonTextBlock->SetText(FText::FromString("Debug : True"));
	}
}
#pragma endregion 

