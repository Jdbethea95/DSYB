// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCreatorWidget.generated.h"


class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UCharacterCreatorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	virtual void Destruct();

	void ShowShop();

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//	UTextBlock* CostDJ;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* LFaceBTN;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* RFaceBTN;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* LBodyBTN;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* RBodyBTN;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextButtonWithIntWidget * Start;
};
