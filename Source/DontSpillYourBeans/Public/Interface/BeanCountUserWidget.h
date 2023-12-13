// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BeanCountUserWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class DONTSPILLYOURBEANS_API UBeanCountUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Text_BeanCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Text_MagicBeanCount;

	UFUNCTION()
		void AddItem(FString itemID);

	void Show();
	void Hide();
};
