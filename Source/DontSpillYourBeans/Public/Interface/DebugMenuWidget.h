// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/BaseMenuVerticalTabsWidget.h"
#include "DebugMenuWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FOnScoreChangedSignature);
UCLASS()
class DONTSPILLYOURBEANS_API UDebugMenuWidget : public UBaseMenuVerticalTabsWidget
{
	GENERATED_BODY()
public:
#pragma region Construction

	UDebugMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void  NativeConstruct()override;


#pragma endregion 



#pragma region Buttons 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Buttons")
		class 	UButtonwWithTextWidget* buttonDebug;



#pragma region Button functionality

	UFUNCTION(BlueprintCallable, Category = "UI|Tab")
	void  ToggleDebug();

#pragma endregion 
#pragma endregion 


};
