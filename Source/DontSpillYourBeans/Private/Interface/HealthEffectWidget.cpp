// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/HealthEffectWidget.h"

void UHealthEffectWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

bool UHealthEffectWidget::Initialize()
{
    Super::Initialize();

    ProgressBar_HP->SetVisibility(ESlateVisibility::Visible);

    appliedDuration = 0.0f;

    return true;
}

void UHealthEffectWidget::Destruct()
{
    Super::Destruct();
}

void UHealthEffectWidget::StartStatusEffect(FLinearColor newColor, float duration)
{
    if (!bIsFlashing)
    {
        StatusEffectRing->SetColorAndOpacity(newColor);
        StartFlash(duration);
    }
}

float UHealthEffectWidget::GetTotalDuration(float duration)
{
    return duration + appliedDuration;
}

void UHealthEffectWidget::StartFlash(float duration)
{
    FLinearColor prevColor = StatusEffectRing->ColorAndOpacity;

    if (bIsFlashing == true && GetWorld()->GetTimerManager().IsTimerActive(StopFlashTimerHandle))
    {
        StopFlashing();
        StatusEffectRing->SetColorAndOpacity(prevColor);
    }

    //I am not flashing
    if (!bIsFlashing)
    {
        if (duration >= 5)
            GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &UHealthEffectWidget::FlashColorChange, 0.5f, true, duration - 5.0f);
        else
            GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &UHealthEffectWidget::FlashColorChange, 0.5f, true, duration);
        
        GetWorld()->GetTimerManager().SetTimer(StopFlashTimerHandle, this, &UHealthEffectWidget::StopFlashing, duration, false);

        //I am not flashing
        bIsFlashing = true;
    }
}

void UHealthEffectWidget::FlashColorChange()
{
    FLinearColor newColor = StatusEffectRing->ColorAndOpacity;

    //UE_LOG(LogTemp, Warning, TEXT("IsClear: %s R: %f G: %f B: %f A: %f"), isClear ? TEXT("True") : TEXT("False"), newColor.R, newColor.G, newColor.B, newColor.A)
    
    if (bIsFlashing)
    {
        if (isClear == false)
        {
            isClear = true;
            newColor.A = 0.0f;
            StatusEffectRing->SetColorAndOpacity(newColor);
        }
        else
        {
            isClear = false;
            newColor.A = 2.0f;
            StatusEffectRing->SetColorAndOpacity(newColor);
        }
    }
}

void UHealthEffectWidget::StopFlashing()
{
    if (bIsFlashing)
    {
        FLinearColor newColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // Stop the flashing effect by clearing the timer.
        GetWorld()->GetTimerManager().ClearTimer(FlashTimerHandle);
        GetWorld()->GetTimerManager().ClearTimer(StopFlashTimerHandle);
        StatusEffectRing->SetColorAndOpacity(newColor);
        bIsFlashing = false;
    }
}
