// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyBoardWidget.generated.h"

/**
 * 
 */
class UButtonwWithTextWidget;
class UButtonPassStringWidget;
class UTextButtonWithIntWidget;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdate);

UCLASS()
class DONTSPILLYOURBEANS_API UKeyBoardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
//	UKeyBoardWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void BindButtons();

  UPROPERTY(BlueprintAssignable)
  FOnUpdate OnEnterPressed;


  UPROPERTY(BlueprintAssignable)
  FOnUpdate OnDeletePressed;


#pragma region Buttons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	UButtonPassStringWidget* buttonEnter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	UTextButtonWithIntWidget* buttonClose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
	UButtonwWithTextWidget* buttonDelete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Output")
	UTextBlock* outputDisplayText;
#pragma endregion 

#pragma region Letter Related


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Keyboard|Data")
	TArray<FString> Letters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Keyboard|Data")
	TArray<UTextButtonWithIntWidget*> buttonsLetters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Keyboard|Output")
	FString outputWord;

#pragma endregion 


	#pragma region  Functionality buttons

	UFUNCTION(BlueprintCallable, Category = "UI|Keyboard Button")
	void Enter();

	UFUNCTION(BlueprintCallable, Category = "UI|Keyboard Button")
	void Delete();


	#pragma endregion

	UFUNCTION(BlueprintCallable, Category = "UI|Keyboard |Output")
	FString GetOutputWord();

	UFUNCTION(BlueprintCallable, Category = "UI|Keyboard |Output")
	void UpdateDisplayText();

	UFUNCTION(BlueprintCallable, Category = "UI|Keyboard |Output")
	FString  GetLetter(int32 lettersIndex);

	UFUNCTION(BlueprintCallable, Category = "UI|Keyboard |Output")
	void PressedALetter(int32 lettersIndex);

};
