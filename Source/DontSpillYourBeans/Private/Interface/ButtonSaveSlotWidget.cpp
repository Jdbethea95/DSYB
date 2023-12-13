// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/ButtonSaveSlotWidget.h"

//UI Widgets coded
#include "Interface/ButtonwWithTextWidget.h"
//Functionality includes
#include "Kismet/GameplayStatics.h"

UButtonSaveSlotWidget::UButtonSaveSlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UButtonSaveSlotWidget::StaticClass();

}

void  UButtonSaveSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}
void  UButtonSaveSlotWidget::OverwriteSave()
{


}

void  UButtonSaveSlotWidget::DeleteSave()
{

	
}
