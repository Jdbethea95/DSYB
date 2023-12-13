// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/BaseScreenWidget.h"
//UI BTN
#include "Interface/ButtonwWithTextWidget.h"


UBaseScreenWidget::UBaseScreenWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UBaseScreenWidget::StaticClass();

}

void UBaseScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}
