// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseItem.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API AConsumableItem : public ABaseItem
{
	GENERATED_BODY()

public:

	AConsumableItem();

	//ID: Determines which item is present (Bean or Consumable)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Info")
		float effectDuration;
};
