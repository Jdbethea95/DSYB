// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "DialogBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UDialogBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//Text Blocks 
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* NPCName_TXT;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Dialog_TXT;

	//Buttons
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BTN_ViewQuest;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BTN_NextPage;

	UFUNCTION()
		void Show();
	UFUNCTION()
		void Hide();
	UFUNCTION()
		void UpdateDialog(FText text);

protected:

private:

	void NativeConstruct();

	void Destruct();
};
