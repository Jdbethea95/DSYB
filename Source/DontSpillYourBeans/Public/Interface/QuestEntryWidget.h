// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UQuestEntryWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativePreConstruct() override;
};
