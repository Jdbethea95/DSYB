// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UBaseScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UBaseScreenWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
	class 	UTextButtonWithIntWidget* buttonClose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Saving")
	TSubclassOf<class UUserWidget> itemButton;
};
