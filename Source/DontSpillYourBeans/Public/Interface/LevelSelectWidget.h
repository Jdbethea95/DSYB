// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LevelSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API ULevelSelectWidget : public UUserWidget
{
	GENERATED_BODY()
public :
	ULevelSelectWidget(const FObjectInitializer& ObjectInitializer);
	virtual void  NativeConstruct()override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class 	UMyGameInstance* GamesInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|")
		int32 CurrTabIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|")
		int32 PrevTabIndex = 0;

#pragma region Buttons Tabs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Tabs")
		class UWidgetSwitcher* TabSwitcher;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ClearChildrenFromScrollBox();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void MakeDebugChildren();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void MakeLevelInfoButtonChildren();
protected:


#pragma endregion 





};
