// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShopKeepAnimation.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UShopKeepAnimation : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void WakeUpShopKeep();
	virtual void SleepNowShopKeep();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float WakeSpeed;

	FTimerHandle handler;

};
