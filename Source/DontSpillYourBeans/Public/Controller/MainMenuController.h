// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"

 
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainMenuController();
	virtual void BeginPlay()override;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* UIMappingContext;
	
};
