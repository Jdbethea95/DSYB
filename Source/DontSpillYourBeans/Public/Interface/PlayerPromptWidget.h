// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PlayerPromptWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UPlayerPromptWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* prompt;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* title;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ButtonClose;
		
	UFUNCTION()
		void Show();
	UFUNCTION()
		void Hide();

protected:

private:

	void NativeConstruct();

	void Destruct();

};
