// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/CharacterCreatorWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
//saving
#include "Interface/TextButtonWithIntWidget.h"
void UCharacterCreatorWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCharacterCreatorWidget::Destruct()
{
	Super::Destruct();
}

void UCharacterCreatorWidget::ShowShop()
{
	APlayerController* controller = GetOwningPlayer();

	if (IsValid(GetWorld()) && IsValid(controller))
	{
		//FInputModeGameAndUI InputMode;
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		controller->SetInputMode(InputMode);

		SetVisibility(ESlateVisibility::Visible);

		controller->bShowMouseCursor = true;
		controller->bEnableClickEvents = true;
		controller->bEnableMouseOverEvents = true;
	}
}




