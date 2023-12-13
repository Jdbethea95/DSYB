// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/BaseMenuWidget.h"

//Functionality includes
#include "Utility/MyGameInstance.h"
//UI BP includes
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
//Other sub menu types
#include "Interface/BaseScreenWidget.h"
#include "Interface/TextButtonWithIntWidget.h"



UBaseMenuWidget::UBaseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UBaseMenuWidget::StaticClass();
	buttonRangeStartIndex = -1;
	buttonRangeStartIndex = -1;
	CurrTabIndex = 0;
}

void UBaseMenuWidget::NativeConstruct()
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

void UBaseMenuWidget::BindButtons()
{
	if (buttonRangeStartIndex == -1)
	{
		buttonRangeStartIndex = 0;
	}
}

void UBaseMenuWidget::BindBackButtons(int screenStart, int ScreenEnd)
{

	//Binding menu back buttons start at 1 if it has a default screen
	for (size_t i = screenStart; i <= ScreenEnd; i++)
	{
		UWidget* menu = MenuSwitcher->GetChildAt(i);
		//check if child widget is a menu screen
		UBaseScreenWidget* screen = Cast<UBaseScreenWidget>(menu);
		if (screen != nullptr)
		{
			if (screen->buttonClose != nullptr)
			{
				screen->buttonClose->buttonWTXT->OnClicked.AddDynamic(this, &UBaseMenuWidget::CloseMenu);

			}
		}
		else
		{
			//check if child is another menu with subscreens
			UBaseMenuWidget* anotherMenuscreen = Cast<UBaseMenuWidget>(menu);
			if (anotherMenuscreen != nullptr)
			{
				anotherMenuscreen->buttonClose->buttonWTXT->OnClicked.AddDynamic(this, &UBaseMenuWidget::CloseMenu);

			}
		}

	}



}

void UBaseMenuWidget::SwitchMenu(int32 tabindex)
{

	SetCurrentTabIndex(tabindex);
	MenuSwitcher->SetActiveWidgetIndex(CurrTabIndex);
	if (GEngine)
	{

		FString DebugMessage = FString::Printf(TEXT("Tab index: %d"), CurrTabIndex);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, DebugMessage);
	}
}
bool  UBaseMenuWidget::CheckifValidTab(int32 tabindex)
{
	if (tabindex < MenuSwitcher->GetChildrenCount() && tabindex > -1)
	{
		return true;

	}
	
	return false;
}
void UBaseMenuWidget::SetCurrentTabIndex(int32 tabindex)
{

	if (CheckifValidTab(tabindex))
	{
		CurrTabIndex = tabindex;
	

	}
}
void UBaseMenuWidget::NextMenu()
{
	int next = CurrTabIndex;
	next++;
	//check if greater than max menus set back to 1 menu
	if (next >= MenuSwitcher->GetChildrenCount())
	{
		SetCurrentTabIndex(0);
		
	}
	else
	{
		//set to next menu
		SetCurrentTabIndex(next);
	}

}
void UBaseMenuWidget::PrevMenu()
{
	int prev = CurrTabIndex;
	prev--;
	//check if greater than max menus set back to 1 menu
	if (prev < MenuSwitcher->GetChildrenCount() && prev > -1)
	{
		//set to next menu
		SetCurrentTabIndex(prev);

	}
	else
	{
		
		SetCurrentTabIndex(0);
	}
}
void UBaseMenuWidget::CloseMenu()
{
	SwitchMenu(DefaultTabIndex);
	SetNextFocus();
}

void UBaseMenuWidget::NextButton()
{
	CycleButtons(true);

}

void UBaseMenuWidget::PrevButton()
{
	CycleButtons(true);
}

int32 UBaseMenuWidget::GetCurrActiveButtonIndex()
{
	return CurrActiveButtonIndex;
}

void UBaseMenuWidget::SetNextFocus()
{



}

bool  UBaseMenuWidget::CheckIfValidButtonIndex(int32 index)
{
	//check if greater than max menus set back to 1 menu
	if (index < buttonRangeEndIndex && index > buttonRangeStartIndex)
	{
		//set to next menu
		SetCurrActiveButtonIndex(index);
		return true;
	}
	return false;
}


void UBaseMenuWidget::SetCurrActiveButtonIndex(int32 index)
{
	if(CheckIfValidButtonIndex( index))
	{
		CurrActiveButtonIndex = index;
	}

}

int UBaseMenuWidget::CycleButtons(bool forward)
{
	if(forward)
	{
		int num = CurrActiveButtonIndex;
		num++;
		SetCurrActiveButtonIndex(num);
		return num;
	}
	else
	{
		int num = CurrActiveButtonIndex;
		num--;
		SetCurrActiveButtonIndex(num);
		return num;
	}
}