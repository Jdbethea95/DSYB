// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/AbilityShopWidget.h"

void UAbilityShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAbilityShopWidget::Destruct()
{
	Super::Destruct();
}

void UAbilityShopWidget::ShowShop()
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

void UAbilityShopWidget::HidShop()
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
