// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/DialogBoxWidget.h"

void UDialogBoxWidget::NativeConstruct()
{
}

void UDialogBoxWidget::Destruct()
{
}

void UDialogBoxWidget::Show()
{
	APlayerController* PC = GetOwningPlayer();

	if (IsValid(GetWorld()) && PC)
	{
		/*FInputModeUIOnly InputMode;*/
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		PC->SetInputMode(InputMode);

		AddToViewport();
		SetIsEnabled(true);
		SetVisibility(ESlateVisibility::Visible);

		//Player Controller Options
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;

	}
}

void UDialogBoxWidget::Hide()
{
	APlayerController* PC = GetOwningPlayer();

	if (PC)
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		PC->SetInputMode(InputMode);

		RemoveFromParent();
		SetIsEnabled(false);

		PC->bShowMouseCursor = false;
	}
}

void UDialogBoxWidget::UpdateDialog(FText text)
{
	Dialog_TXT->SetText(text);
}
