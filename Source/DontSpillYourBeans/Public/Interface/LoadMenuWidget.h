// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseScreenWidget.h"
#include "LoadMenuWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeleteSave);
UCLASS()
class DONTSPILLYOURBEANS_API ULoadMenuWidget :public UBaseScreenWidget
{
	GENERATED_BODY()
public:

	ULoadMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void BindButtons();

	/// <summary>
	/// used to broadcast saving changes
	/// </summary>
	UPROPERTY(VisibleAnyWhere, BlueprintAssignable)
	FOnDeleteSave OnsaveDeleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class 	UMyGameInstance* GamesInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
	class 	UTextButtonWithIntWidget* buttonDeleteAllSaves;

   UFUNCTION(BlueprintCallable)
    void MakeLoadButtons();
	
	UFUNCTION(BlueprintCallable, Category = "UI|Setup")
	void CreateSaveSlotButton(FText name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Buttons")
	TSubclassOf<class UUserWidget> SaveSlotButtonClass;

	//Save slots
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* ScrollBoxSaveSlots;


	UFUNCTION(BlueprintCallable, Category = "UI|Tab")
	void DeleteSave(int32 index);

	UFUNCTION(BlueprintCallable, Category = "UI|Tab")
	void DeleteAllSaves();
};
