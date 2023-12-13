// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseMenuWidget.h"
#include "BaseMenuHorizontalTabsWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UBaseMenuHorizontalTabsWidget : public UBaseMenuWidget
{
	GENERATED_BODY()
public:
	UBaseMenuHorizontalTabsWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
/// <summary>
/// binds tab buttons to open their sub menu
/// </summary>
	void BindButtons()override;
	void NextMenu()override;
	void PrevMenu()override;

	void NextButton()override;
	void PrevButton()override;
	/// <summary>
/// horizontal holds the buttons used to open "tabs" aka other menus 
/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Tab")
	class UHorizontalBox* tabButtons;

};
