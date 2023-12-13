// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseItem.h"
#include "BeanItem.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API ABeanItem : public ABaseItem
{
	GENERATED_BODY()

public:

	ABeanItem();

	void Use() override;
};
