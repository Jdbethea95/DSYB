// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/QuestLogWidget.h"

void UQuestLogWidget::Show()
{
	APlayerController* PC = GetOwningPlayer();

	if (IsValid(GetWorld()) && PC)
	{
		/*FInputModeUIOnly InputMode;*/
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		PC->SetInputMode(InputMode);

		AddToViewport();
		SetVisibility(ESlateVisibility::Visible);
		SetIsEnabled(true);

		//Player Controller Options
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;

	}
}

void UQuestLogWidget::Hide()
{
	APlayerController* PC = GetOwningPlayer();

	if (PC)
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		PC->SetInputMode(InputMode);

		RemoveFromParent();
		SetIsEnabled(false);

		PC->bShowMouseCursor = false;
	}
}

bool UQuestLogWidget::PlayQuestDescriptionAnim(EUMGSequencePlayMode::Type PlayMode, float StartAtTime, int32 NumLoopsToPlay, float PlaybackSpeed)
{
	if (DescriptionExpand && !IsAnimationPlaying(DescriptionExpand))
	{
		UE_LOG(LogTemp, Warning, TEXT("Animation Valid"));
		PlayAnimation(DescriptionExpand, StartAtTime, NumLoopsToPlay, PlayMode, PlaybackSpeed);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Animation InValid"));
		return false;
	}
		
}

void UQuestLogWidget::Expand()
{
	UE_LOG(LogTemp, Warning, TEXT("Expand Function Start"));
	PlayQuestDescriptionAnim();
}

void UQuestLogWidget::Shrink()
{
	UE_LOG(LogTemp, Warning, TEXT("Shrink Function Start"));
	PlayQuestDescriptionAnim(EUMGSequencePlayMode::Reverse);
}

void UQuestLogWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UQuestLogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BTN_Exit) && IsValid(BTN_Expand) && IsValid(BTN_Expand))
	{
		BTN_Exit->OnClicked.AddUniqueDynamic(this, &UQuestLogWidget::Hide);
		BTN_Expand->OnClicked.AddUniqueDynamic(this, &UQuestLogWidget::Expand);
		BTN_Shrink->OnClicked.AddUniqueDynamic(this, &UQuestLogWidget::Shrink);
	}
	
	
}

void UQuestLogWidget::Destruct()
{
	Super::Destruct();

}
