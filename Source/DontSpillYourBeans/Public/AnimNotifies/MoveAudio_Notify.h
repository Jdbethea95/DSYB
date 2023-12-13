// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AI/Characters/BaseAICharacter.h"
#include "MoveAudio_Notify.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UMoveAudio_Notify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
