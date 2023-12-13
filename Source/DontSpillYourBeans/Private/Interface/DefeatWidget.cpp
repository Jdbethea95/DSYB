// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/DefeatWidget.h"
//UI
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDefeatWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UDefeatWidget::ShowDefeatScreen()
{
	APlayerController* controller = GetOwningPlayer();

	if (IsValid(GetWorld()) && IsValid(controller))
	{
	
		FInputModeUIOnly  InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		controller->SetInputMode(InputMode);

		SetVisibility(ESlateVisibility::Visible);
		controller->bShowMouseCursor = true;
		controller->bEnableClickEvents = true;
		controller->bEnableMouseOverEvents = true;
	}
}

void UDefeatWidget::HideDefeatScreen()
{
	APlayerController* controller = GetOwningPlayer();

	if (IsValid(controller))
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		controller->SetInputMode(InputMode);

		SetVisibility(ESlateVisibility::Hidden);

		controller->bShowMouseCursor = false;
	}
}
