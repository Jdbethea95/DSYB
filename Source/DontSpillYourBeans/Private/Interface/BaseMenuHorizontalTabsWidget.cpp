// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/BaseMenuHorizontalTabsWidget.h"
//-----------------UI Widgets coded
#include "Interface/ButtonwWithTextWidget.h"
#include "Interface/TextButtonWithIntWidget.h"
//other menu types
#include "Interface/BaseMenuVerticalTabsWidget.h"
//-------------------UI BP includes
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
//UI BP includes specic to this menu 
#include "Components/HorizontalBox.h"

UBaseMenuHorizontalTabsWidget::UBaseMenuHorizontalTabsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UBaseMenuHorizontalTabsWidget::StaticClass();

}

void UBaseMenuHorizontalTabsWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseMenuHorizontalTabsWidget::BindButtons()
{
	Super::BindButtons();
	// Binding tab buttons
//get number of menus 
	int menusCount = MenuSwitcher->GetChildrenCount();
	//set to start of sub menus 
	int numMenuBindStartNumber = 0;
	//check for default menu
	if (hasDefaultMenu)
	{
		//subtract default screen aka screen 0 if there is one
		menusCount--;
		// 1 to exclude the default
		numMenuBindStartNumber = 1;
	}
	//if has an end range number
	if (buttonRangeEndIndex == -1)
	{//careful to not have spacers in the box
		buttonRangeEndIndex = tabButtons->GetChildrenCount();
	}
	//To check buttons and menus line up in count
	int numBtnCount = tabButtons->GetChildrenCount();
	//check the amount of menus match match btn count  
	if (menusCount == numBtnCount)
	{

		//loop buttons and hook them to their respective screens
		for (size_t j = buttonRangeStartIndex; j < buttonRangeEndIndex; j++)
		{
			//Dont shift start since buttons dont have a default
			for (size_t i = 0; i < numBtnCount; i++)
			{
				//get button 
				UTextButtonWithIntWidget* btn = Cast<UTextButtonWithIntWidget>(tabButtons->GetChildAt(j));
				//bind it
				if (btn != nullptr)
				{
					int index = i;
					if (hasDefaultMenu)
					{
						//index of the menu + 1 since zero is the default screen
						index += 1;
					}
					//set menu number
					btn->number = index;
					//bind opening menu
					btn->OnPassNumber.AddDynamic(this, &UBaseMenuWidget::SwitchMenu);

				}
			}

		}
		BindBackButtons(numMenuBindStartNumber, menusCount);
	}

	
}


void UBaseMenuHorizontalTabsWidget::NextMenu()
{
	Super::NextMenu();

}

void UBaseMenuHorizontalTabsWidget::PrevMenu()
{
}

void UBaseMenuHorizontalTabsWidget::NextButton()
{
}

void UBaseMenuHorizontalTabsWidget::PrevButton()
{
}
