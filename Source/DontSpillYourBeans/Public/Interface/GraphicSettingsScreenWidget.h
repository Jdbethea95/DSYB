// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseScreenWidget.h"
#include "GraphicSettingsScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UGraphicSettingsScreenWidget : public UBaseScreenWidget
{
	GENERATED_BODY()

public :
	UGraphicSettingsScreenWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UGameUserSettings* GameSettings;

	//window 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
	class UComboBoxString* DisplayModeComboBox;

	UFUNCTION(BlueprintCallable)
	void SetDisplayMode(FString SelectedItem, enum ESelectInfo::Type SelectionType);

	// confirm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
	class 	UButtonwWithTextWidget* buttonConfirm;

	UFUNCTION(BlueprintCallable)
	void ConfirmSettings();
	
};
