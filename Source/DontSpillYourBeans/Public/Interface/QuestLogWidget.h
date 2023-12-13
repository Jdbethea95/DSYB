// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "QuestLogWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UQuestLogWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Animations
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* DescriptionExpand;

	//Scroll Boxes
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UScrollBox* ActiveQuestsScrollBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UScrollBox* CompletedQuestsScrollBox;

	//Text Blocks
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* QuestDescription_TXT;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* StageDescription_TXT;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* RewardCount_TXT;

	//Buttons
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BTN_Shrink;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BTN_Expand;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BTN_Exit;

	UFUNCTION()
		void Show();
	UFUNCTION()
		void Hide();

		bool PlayQuestDescriptionAnim(EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float StartAtTime = 0.0F, int32 NumLoopsToPlay = 1, float PlaybackSpeed = 1.0f);

	UFUNCTION()
		void Expand();
	UFUNCTION()
		void Shrink();

protected:

private:

	void NativePreConstruct() override;

	void NativeConstruct();

	void Destruct();

};
