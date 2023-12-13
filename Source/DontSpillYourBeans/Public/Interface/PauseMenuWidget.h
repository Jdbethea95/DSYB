// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseMenuVerticalTabsWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UPauseMenuWidget : public UBaseMenuVerticalTabsWidget
{
	GENERATED_BODY()
public:

	UPauseMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void BindButtons()override;
	 void CloseMenu()override;
	

	//buttons  that are unique
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
		class 	UButtonwWithTextWidget* buttonResume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
		class 	UButtonwWithTextWidget* buttonHUB;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
		class 	UButtonwWithTextWidget* buttonMainMenu;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
		class 	UButtonwWithTextWidget* buttonQuit;

		//index of special child buttons
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tab")
		int32 LoadButtonIndex = 1;
	//buton func
	UFUNCTION(BlueprintCallable, Category = "UI|Button")
		void ClosePauseMenu();

	UFUNCTION(BlueprintCallable, Category = "UI|Button")
		void Resume();

	UFUNCTION(BlueprintCallable, Category = "UI|Button")
		void ToggleLoadButtonEnable();

private:
	UPROPERTY()
	class UTextButtonWithIntWidget* loadBtn;

};
