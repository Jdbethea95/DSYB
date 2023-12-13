// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EggyAnimEventGraph.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UEggyAnimEventGraph : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void ActivateAttack();
	virtual void DeactivateAttack();
	virtual void ActivateHurt();
	virtual void DeactivateHurt();
	virtual void DeathState(bool isDead);

	virtual void PlaySpecialAction();

	bool IsHurt();
protected:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Speed;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Attack;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Hurt;
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		bool Death;


//Slots used when able by the AI.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimSequence* SpecialAction;

};
