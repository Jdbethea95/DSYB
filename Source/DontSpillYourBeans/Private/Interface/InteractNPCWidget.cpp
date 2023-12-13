// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/InteractNPCWidget.h"

void UInteractNPCWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInteractNPCWidget::Destruct()
{
	Super::Destruct();

}

void UInteractNPCWidget::Show()
{

	if (IsValid(GetWorld()))
	{
		APlayerController* PC = GetOwningPlayer();
		if (PC)
		{

			AddToViewport();
			SetIsEnabled(true);

		}
	}

}

void UInteractNPCWidget::Hide()
{

	APlayerController* PC = GetOwningPlayer();
	if (PC)
	{

		RemoveFromParent();
		SetIsEnabled(false);

	}

}