// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ButtonwWithTextWidget.h"
#include "TextButtonWithIntWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPassParam, int32, number);
UCLASS()
class DONTSPILLYOURBEANS_API UTextButtonWithIntWidget : public UButtonwWithTextWidget
{
	GENERATED_BODY()
	

	
public:

	virtual void NativeConstruct() override;
	UPROPERTY(BlueprintAssignable)
	FOnPassParam OnPassNumber;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PassNumber();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Button")
	int32 number = 0;


#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
#endif

};
