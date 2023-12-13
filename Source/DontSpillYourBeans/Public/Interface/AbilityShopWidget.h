// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "AbilityShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UAbilityShopWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void NativeConstruct() override;
	virtual void Destruct();

	void ShowShop();
	void HidShop();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CostDur;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CostCap;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CostHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CostDJ;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ButtonDur;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ButtonCap;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ButtonHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ButtonDJ;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ExitButton;
};
