// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/PlayerSwingStart.h"

void UPlayerSwingStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (IsValid(Player))
	{
		Player->StartAttack();
	}
}
