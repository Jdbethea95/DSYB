// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AI/Characters/BaseAICharacter.h"
#include "AttackEnd.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UAttackEnd : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	ABaseAICharacter* Enemy;
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
