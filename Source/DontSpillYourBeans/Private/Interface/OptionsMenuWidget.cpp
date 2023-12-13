// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/OptionsMenuWidget.h"
//UI Widgets coded
#include "Interface/ButtonwWithTextWidget.h"
#include "Interface/TextButtonWithIntWidget.h"

//Loading
#include "Interface/NewSaveMenuWidget.h"
#include "Interface/LoadMenuWidget.h"
//UI BP includes
//UI BP includes
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
UOptionsMenuWidget::UOptionsMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UOptionsMenuWidget::StaticClass();
}

void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UOptionsMenuWidget::BindButtons()
{
	Super::BindButtons();
}

