// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractNPCWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UInteractNPCWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
		void Show();
	UFUNCTION()
		void Hide();

protected:

private:

	void NativeConstruct();

	void Destruct();
};
