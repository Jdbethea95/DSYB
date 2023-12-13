// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/BeanCountUserWidget.h"

void UBeanCountUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBeanCountUserWidget::AddItem(FString itemID)
{
}

void UBeanCountUserWidget::Show()
{
	//UE_LOG(LogTemp, Warning, TEXT("FO_SHOW."))
		AddToViewport(9999);
}

void UBeanCountUserWidget::Hide()
{
	//UE_LOG(LogTemp, Warning, TEXT("NO_SHOW"))
	RemoveFromParent();
}
