// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/QuestGiverWidget.h"

void UQuestGiverWidget::NativeConstruct()
{
}

void UQuestGiverWidget::Destruct()
{
}

void UQuestGiverWidget::Show()
{
	APlayerController* PC = GetOwningPlayer();

	if (IsValid(GetWorld()) && PC)
	{
			/*FInputModeUIOnly InputMode;*/
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PC->SetInputMode(InputMode);

			AddToViewport();
			SetVisibility(ESlateVisibility::Visible);
			SetIsEnabled(true);

			//Player Controller Options
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;

	}
}

void UQuestGiverWidget::Hide()
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


