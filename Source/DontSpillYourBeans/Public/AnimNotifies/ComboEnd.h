// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Pawn/BaseCharacter.h"
#include "ComboEnd.generated.h"


/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UComboEnd : public UAnimNotify
{
	GENERATED_BODY()

	ABaseCharacter* Player;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
