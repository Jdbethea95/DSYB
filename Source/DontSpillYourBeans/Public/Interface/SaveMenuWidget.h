// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseMenuWidget.h"
#include "SaveMenuWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSave);
UCLASS()
class DONTSPILLYOURBEANS_API USaveMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()
	
public:

	USaveMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;


	void BindButtons()override;
	UPROPERTY(VisibleAnyWhere,BlueprintAssignable)
	FOnSave Onsavechange;
	//func
	UFUNCTION(BlueprintCallable, Category = "UI|Setup")
		void CreateSaveSlotButton(FText name);
	UFUNCTION(BlueprintCallable, Category = "UI|Setup")
		void MakeNewSave(FString SaveName);

		UFUNCTION(BlueprintCallable, Category = "UI|Setup")
		void MakeSaveFilesButtons();

	UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		void RemoveSaveSlot(int32 index);

		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		void DeleteSave(int32 index);

		UFUNCTION(BlueprintCallable, Category = "UI|Tab")
		void OverwriteSave(int32 index);

	// new save window
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
		class 	UButtonwWithTextWidget* buttonNewSave;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Buttons")
		class 	UNewSaveMenuWidget* newSaveMenu;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Buttons")
		TSubclassOf<class UUserWidget> SaveSlotButtonClass;

		//Save slots
		UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UScrollBox* ScrollBoxSaveSlots;


	

};
