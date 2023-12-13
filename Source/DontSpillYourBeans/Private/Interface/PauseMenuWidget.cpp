// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/PauseMenuWidget.h"
//resume 
#include "Kismet/GameplayStatics.h"
#include "Pawn/BaseCharacter.h"
//Functionality includes
#include "Utility/MyGameInstance.h"
//UI BP includes
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
//UI Widgets coded
#include "Interface/ButtonwWithTextWidget.h"
#include "Interface/TextButtonWithIntWidget.h"

//UI buttons 
#include "Interface/ButtonSaveSlotWidget.h"
//-------------------------------------------------Menus
#include "Interface/SaveMenuWidget.h"
#include "Interface/NewSaveMenuWidget.h"
//Loading
#include "Interface/LoadMenuWidget.h"

UPauseMenuWidget::UPauseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UPauseMenuWidget::StaticClass();

}

void  UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	  
	if (nullptr != GamesInstance)
	{

		ToggleLoadButtonEnable();

	}
	
}
void UPauseMenuWidget::ToggleLoadButtonEnable()
{
	if (nullptr != GamesInstance)
	{
      if (loadBtn != nullptr)
      {
		  loadBtn->SetIsEnabled(GamesInstance->savingData.saveFilesExist);
		//load menu buttons

      }

	}
}

void UPauseMenuWidget::BindButtons()
{
  Super::BindButtons();

////need to convert pause controller to c++
//buttonResume->buttonWTXT->OnClicked.AddDynamic(this, &UPauseMenuWidget::Resume);
buttonHUB->buttonWTXT->OnClicked.AddDynamic(GamesInstance, &UMyGameInstance::LoadMapHUB);
buttonMainMenu->buttonWTXT->OnClicked.AddDynamic(GamesInstance, &UMyGameInstance::LoadMainMenu);
buttonQuit->buttonWTXT->OnClicked.AddDynamic(GamesInstance, &UMyGameInstance::QuitGame);

//Toggle Load Btn
UTextButtonWithIntWidget* btn = Cast<UTextButtonWithIntWidget>(tabButtons->GetChildAt(LoadButtonIndex));

if (btn != nullptr)
{
	loadBtn = btn;
  //bind toggling
  USaveMenuWidget* MenuSave = Cast <USaveMenuWidget >(MenuSwitcher->GetWidgetAtIndex(1));
  if (MenuSave != nullptr)
  {

  	MenuSave->Onsavechange.AddDynamic(this, &UPauseMenuWidget::ToggleLoadButtonEnable);

	//load menu save slot buttons update
	ULoadMenuWidget* Loadwidget = Cast <ULoadMenuWidget >(MenuSwitcher->GetWidgetAtIndex(1));
	if (Loadwidget != nullptr)
	{
		MenuSave->Onsavechange.AddDynamic(Loadwidget, &ULoadMenuWidget::MakeLoadButtons);
		Loadwidget->OnsaveDeleted.AddDynamic(this, &UPauseMenuWidget::ToggleLoadButtonEnable);
	}
  }
}
//Hide hub load btn
if (GamesInstance->CurrentLevelIndex == GamesInstance->HubIndex)
{
	buttonHUB->SetVisibility(ESlateVisibility::Hidden);

}

}
void UPauseMenuWidget::CloseMenu()
{
	
	Super::CloseMenu();
	
}
void UPauseMenuWidget::ClosePauseMenu()
{
	CloseMenu();
	this->RemoveFromParent();
}
void UPauseMenuWidget::Resume()
{
	//TO DO :
	ABaseCharacter* player = Cast< ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player != nullptr)
	{
		//player->execTogglePauseMenu(player->TogglePause());
	}
}