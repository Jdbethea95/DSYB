// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Utility/EggyAnimEventGraph.h"
#include "HurtEnd.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UHurtEnd : public UAnimNotify
{
	GENERATED_BODY()
private:
	UEggyAnimEventGraph* animGraph;
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
