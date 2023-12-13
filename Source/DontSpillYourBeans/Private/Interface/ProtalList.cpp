// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/ProtalList.h"
#include "Interface/PortalObject.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"

void UProtalList::NativeConstruct()
{
	Super::NativeConstruct();


}

void UProtalList::Destruct()
{
	Super::Destruct();
}

void UProtalList::ShowList()
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

void UProtalList::HideList()
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
