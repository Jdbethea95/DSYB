// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseMenuVerticalTabsWidget.h"
#include "OptionsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UOptionsMenuWidget : public UBaseMenuVerticalTabsWidget
{
	GENERATED_BODY()
	
public:
	UOptionsMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void BindButtons()override;

};
