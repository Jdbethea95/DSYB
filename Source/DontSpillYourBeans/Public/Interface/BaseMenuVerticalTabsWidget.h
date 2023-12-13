// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseMenuWidget.h"
#include "BaseMenuVerticalTabsWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UBaseMenuVerticalTabsWidget : public UBaseMenuWidget
{
	GENERATED_BODY()
public:
	UBaseMenuVerticalTabsWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	/// <summary>
	/// binds tab buttons to open their sub menu
	/// </summary>
	void BindButtons()override;
	void NextMenu()override;
	void PrevMenu()override;
	void CloseMenu()override;
	void SetNextFocus()override;
	/// <summary>
/// vertical holds the buttons used to open "tabs" aka other menus 
/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Tab")
	class UVerticalBox* tabButtons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tab")
	bool HasSpacers;
};
