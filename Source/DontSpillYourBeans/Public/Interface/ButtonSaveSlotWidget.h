// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonSaveSlotWidget.generated.h"

/**
 * 
 */


UCLASS()
class DONTSPILLYOURBEANS_API UButtonSaveSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	

	UButtonSaveSlotWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
		class 	UTextButtonWithIntWidget* buttonSaveSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
		class 	UTextButtonWithIntWidget* buttonDeleteSave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Save Info")
		FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Buttons")
		int32 childIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "UI|Save")
		void  OverwriteSave();

	UFUNCTION(BlueprintCallable, Category = "UI|Save")
		void  DeleteSave();

};
