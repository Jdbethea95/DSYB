// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API URaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	virtual void Destruct();
	

	void ShowLaps();
	void HideLaps();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* LapCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* LapTitle;

protected:
	FTimerHandle handler;

};
