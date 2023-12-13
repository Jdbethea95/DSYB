// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY(Abstract)
public:
	UBaseMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class 	UMyGameInstance* GamesInstance;
	/// <summary>
	/// Used to bind the buttons to their associated tabs automatically
	/// Also sets those buttons indexs apropriatly so u dont need to do so in bp
	/// careful of widgets in the associated vertical box
	/// this function doesnt diferientiate the children and counts all
	/// btn and menu count need to match to parent buttons
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void BindButtons();


	/// <summary>
	/// holds the sub menus Widgets and the default as index 0
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Tab")
	class UWidgetSwitcher* MenuSwitcher;
	/// <summary>
	/// Binds back Buttons in submenus
	/// </summary>
	/// <param name="screenStart"></param>
	/// <param name="ScreenEnd"></param>
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void BindBackButtons(int screenStart,int ScreenEnd);
	/// <summary>
	/// //used to close the window when it is a child
	///  incase of main menu its disabled
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
	class 	UButtonwWithTextWidget* buttonClose;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tab")
		int32 CurrTabIndex;

		/// <summary>
		/// the buttons use this to "open" their associated menu
		/// </summary>
		/// <param name="tabindex"></param>
		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		virtual void SwitchMenu(int32 tabindex);

		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		bool CheckifValidTab(int32 tabindex);

		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		void SetCurrentTabIndex(int32 tabindex);
	
		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		virtual void NextMenu();
		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		virtual void PrevMenu();
		/// <summary>
	/// sets widget switcher to DefaultTabIndex which is 
	/// 0 wich is by defualt
	/// </summary>
		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		virtual void CloseMenu();



		/// <summary>
		/// false will decrement and true increment
		/// </summary>
		/// <param name=""></param>
		int CycleButtons(bool forward);
		/// <summary>
		/// Used to set the menu that when sub menus close is called it is opened
		/// </summary>
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tab")
		int32 DefaultTabIndex = 0;
		/// <summary>
		/// This is to set if there is or isnt a  default menu
		// which is set in DefaultTabIndex
		/// </summary>
		/// <returns></returns>
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tab")
		bool hasDefaultMenu = true;

		/// <summary>
		/// used for button binding to determine where they start
		/// if left at -1 will stat at zero
		/// </summary>
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tab")
		int32 buttonRangeStartIndex;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tab")
		int32 buttonRangeEndIndex;

		virtual void NextButton();
		virtual void PrevButton();
		/// </summary>
		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		virtual void SetNextFocus();
		bool CheckIfValidButtonIndex(int32 index);
		void SetCurrActiveButtonIndex(int32 index);
		int32 GetCurrActiveButtonIndex();
private:
	/// <summary>
/// Index of hilighted button
/// </summary>
	UPROPERTY()
	int32 CurrActiveButtonIndex;
};
