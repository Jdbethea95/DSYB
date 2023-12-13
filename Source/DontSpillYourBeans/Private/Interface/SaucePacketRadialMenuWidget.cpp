// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/SaucePacketRadialMenuWidget.h"

void USaucePacketRadialMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void USaucePacketRadialMenuWidget::Destruct()
{
	Super::Destruct();
}

void USaucePacketRadialMenuWidget::AddItem(FString itemID)
{
}

void USaucePacketRadialMenuWidget::Show()
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

void USaucePacketRadialMenuWidget::Hide()
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