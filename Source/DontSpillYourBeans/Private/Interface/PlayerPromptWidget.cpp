// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/PlayerPromptWidget.h"

void UPlayerPromptWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonClose->OnClicked.AddUniqueDynamic(this, &UPlayerPromptWidget::Hide);

}

void UPlayerPromptWidget::Destruct()
{
	Super::Destruct();

}

void UPlayerPromptWidget::Show()
{
	if (IsValid(GetWorld()))
	{
		APlayerController* PC = GetOwningPlayer();
		if (PC)
		{
			/*FInputModeUIOnly InputMode;*/
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PC->SetInputMode(InputMode);

			AddToViewport();
			SetIsEnabled(true);

			//Player Controller Options
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;

		}
	}
}

void UPlayerPromptWidget::Hide()
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