// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PortalObject.generated.h"


class UTextBlock;
class UTextButtonWithIntWidget;
class UImage;
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UPortalObject : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void NativeConstruct() override;
	virtual void Destruct();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextButtonWithIntWidget* PortalButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
		UImage* PortalImage;
};
