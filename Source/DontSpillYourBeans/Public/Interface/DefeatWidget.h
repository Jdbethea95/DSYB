// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DefeatWidget.generated.h"

//Forward declaring
class UButton;
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UDefeatWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	 UButton* RespawnButton;
	

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	 UButton* MainMenuButton;

	 UFUNCTION(BlueprintCallable, Category = "UI")
	 void ShowDefeatScreen();

	 UFUNCTION(BlueprintCallable, Category = "UI")
	 void HideDefeatScreen();
};
