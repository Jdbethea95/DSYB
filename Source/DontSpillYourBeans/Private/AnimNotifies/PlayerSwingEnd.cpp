// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/PlayerSwingEnd.h"

void UPlayerSwingEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (IsValid(Player))
	{
		Player->EndAttack();
	}
}
