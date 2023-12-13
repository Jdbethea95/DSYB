// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthEffectWidget.generated.h"

/**
 * 
 */

UCLASS()
class DONTSPILLYOURBEANS_API UHealthEffectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeConstruct() override;
	bool Initialize() override;
	virtual void Destruct();

	//Widget Binds
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* StatusEffectRing;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* ProgressBar_HP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Text_CurrentHealth;

	void StartStatusEffect(FLinearColor newColor, float duration = 5.0f);
	
	float GetTotalDuration(float duration = 5.0f);

	bool bIsFlashing = false;
	
	float appliedDuration;

protected:

	float effectDuration;

private:

	FTimerHandle FlashTimerHandle;
	FTimerHandle StopFlashTimerHandle;

	bool isClear = false;

	void StartFlash(float duration = 5.0f);
	void FlashColorChange();
	void StopFlashing();

};
