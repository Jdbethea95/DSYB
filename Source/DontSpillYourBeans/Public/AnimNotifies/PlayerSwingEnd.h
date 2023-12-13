// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Pawn/BaseCharacter.h"
#include "PlayerSwingEnd.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UPlayerSwingEnd : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
