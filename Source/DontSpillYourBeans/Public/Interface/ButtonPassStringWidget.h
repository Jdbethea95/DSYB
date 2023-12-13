// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ButtonwWithTextWidget.h"
#include "ButtonPassStringWidget.generated.h"

/**
 * 
 */
class UButton;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPassAWord, FString, word);
UCLASS()
class DONTSPILLYOURBEANS_API UButtonPassStringWidget :  public UButtonwWithTextWidget
{
	GENERATED_BODY()

public:


	 void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable)
	FOnPassAWord OnPassAWord;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PassAWord();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Button")
	FString word;







};
