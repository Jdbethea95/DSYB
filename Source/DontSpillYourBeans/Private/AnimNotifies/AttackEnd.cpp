// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AttackEnd.h"

void UAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Enemy = Cast<ABaseAICharacter>(MeshComp->GetOwner());

	if (IsValid(Enemy))
	{
		Enemy->EndAttackCall();
	}
}
