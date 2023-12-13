// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/RaceWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"

void URaceWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URaceWidget::Destruct()
{
	Super::Destruct();
}

void URaceWidget::ShowLaps()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(handler))
	{
		GetWorld()->GetTimerManager().ClearTimer(handler);
	}

	SetVisibility(ESlateVisibility::Visible);
}

void URaceWidget::HideLaps()
{

	GetWorld()->GetTimerManager().SetTimer(handler, [&]() {	SetVisibility(ESlateVisibility::Hidden); }, 5.0f, false);

}


