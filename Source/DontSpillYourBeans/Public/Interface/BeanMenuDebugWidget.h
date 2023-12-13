// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseScreenWidget.h"
#include "BeanMenuDebugWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UBeanMenuDebugWidget : public UBaseScreenWidget 
{
	GENERATED_BODY()
	
public:

	//UBeanMenuDebugWidget(const FObjectInitializer& ObjectInitializer);
	//virtual void NativeConstruct() override;

	//buttons 

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "UI|Input")
	FText nameOfItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	class UTextBlock* buttonTextBlock;
	//2DTexture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Display")
	class UTexture2D* sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class	UEditableTextBox* amountInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	class 	UButtonwWithTextWidget* buttonIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	class 	UButtonwWithTextWidget* buttonDecrease;



};
