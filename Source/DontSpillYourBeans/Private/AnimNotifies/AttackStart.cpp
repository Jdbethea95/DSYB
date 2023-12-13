// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AttackStart.h"


void UAttackStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Enemy = Cast<ABaseAICharacter>(MeshComp->GetOwner());

	if (IsValid(Enemy) && Enemy->IsAlive())
	{
		Enemy->AttackCall();
	}
}
