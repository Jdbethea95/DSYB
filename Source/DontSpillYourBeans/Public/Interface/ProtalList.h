// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProtalList.generated.h"


class UPortalObject;
class UScrollBox;
class UButton;
/**
 *
 */
UCLASS()
class DONTSPILLYOURBEANS_API UProtalList : public UUserWidget
{
	GENERATED_BODY()


public:
	void NativeConstruct() override;
	virtual void Destruct();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "List Entry")
		TSubclassOf<UPortalObject> EntryObject;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UScrollBox* PortalListView;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ExitButton;

	void ShowList();
	UFUNCTION()
		void HideList();

};
