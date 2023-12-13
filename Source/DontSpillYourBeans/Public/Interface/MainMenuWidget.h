// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseMenuVerticalTabsWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */

UCLASS()
class DONTSPILLYOURBEANS_API UMainMenuWidget : public UBaseMenuVerticalTabsWidget
{
	GENERATED_BODY()

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void BindButtons()override;
	UFUNCTION(BlueprintCallable, Category = "UI|Button")
	void ToggleLoadMenuUI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Button")
	int32 LoadButtonIndex;

#pragma region buttons
	//BUTTONS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	class 	UTextButtonWithIntWidget* buttonplay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	class 	UTextButtonWithIntWidget* buttonNewGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	class 	UButtonwWithTextWidget* buttonQuit;

#pragma endregion 


	
};
