// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "SaucePacketRadialMenuWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class DONTSPILLYOURBEANS_API USaucePacketRadialMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;
	virtual void Destruct();

	//Packet Counts (Green, Yellow, Red, Grey)
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TopLeftCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TopCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TopRightCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* RightCount;

	//Packet Images (Green, Yellow, Red, Grey)
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* TopLeftImg;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* TopImg;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* TopRightImg;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* RightImg;

	//Buttons (Green, Yellow, Red, Grey)
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* TopLeftBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* TopBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* TopRightBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* RightBtn;

	UFUNCTION()
		void AddItem(FString itemID);

	void Show();
	void Hide();
	
};
