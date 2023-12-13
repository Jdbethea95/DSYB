// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DebugAddItemButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UDebugAddItemButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UDebugAddItemButtonWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	//buttons 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Input")
	FText nameOfItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	class UTextBlock* nameTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Button")
	float fontSize;

	//2DTexture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Display")
	class UTexture2D* sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class	UEditableTextBox* amountInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	class 	UTextButtonWithIntWidget* buttonConfirmAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	class UTextBlock* currentAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	class 	UTextButtonWithIntWidget* buttonIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	class 	UTextButtonWithIntWidget* buttonDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	class 	UTextButtonWithIntWidget* buttonMaxAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Button")
	int IncrementAmount;


	void BindButtons();
	int IncrementItem(int32 amount,bool add);
	void SetNameText(FText name);
	void UpdateFontSize();


#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
#endif

};
