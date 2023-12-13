// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseScreenWidget.h"
#include "NewSaveMenuWidget.generated.h"

/**
 * 
 */
class   UWidgetSwitcher;
class   UTextBlock;
class	UEditableTextBox;
class   UKeyBoardWidget;

class	UButtonPassStringWidget;
class 	UMyGameInstance;
UCLASS()
class DONTSPILLYOURBEANS_API UNewSaveMenuWidget : public UBaseScreenWidget
{
	GENERATED_BODY()
	
public:

	UNewSaveMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	 UMyGameInstance* GamesInstance;

	//buttons 
	virtual void BindButtons();
	/// <summary>
	/// Output display swamp for keyboard and virtual keyboard
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	UWidgetSwitcher* inputDisplaySwitcher;
	/// <summary>
	/// keyboard display
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	UEditableTextBox* EditableTextBoxInput;

	/// <summary>
	/// virtual keybaord output
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
	UTextBlock* inputDisplayTextBlock;


	/// <summary>
/// keyboard & mouse  confirm
/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	UButtonPassStringWidget* buttonConfirm;

		/// <summary>
		/// virtual keyboard
		/// </summary>
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Input")
		UKeyBoardWidget* keyboardVirtual;

		UFUNCTION(BlueprintCallable, Category = "UI|Button")
		void NewGame(FString SaveName);

		UFUNCTION(BlueprintCallable, Category = "UI|Button")
		void ControllerNewGame(FString SaveName);


		
};