// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "QuestGiverWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UQuestGiverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Text Blocks 
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* QuestTitle_TXT;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* QuestDescription_TXT;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* StageDescription_TXT;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Objectives_TXT;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* RewardCount_TXT;

	//Buttons
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BTN_Decline;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BTN_Accept;

	UFUNCTION()
		void Show();
	UFUNCTION()
		void Hide();

protected:

private:

	void NativeConstruct();

	void Destruct();
};
