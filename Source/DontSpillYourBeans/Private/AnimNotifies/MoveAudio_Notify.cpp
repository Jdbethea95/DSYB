// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/MoveAudio_Notify.h"

void UMoveAudio_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABaseAICharacter* Enemy = Cast<ABaseAICharacter>(MeshComp->GetOwner());

	if (IsValid(Enemy) && Enemy->IsAlive())
	{
		Enemy->PlayMovementAudio();
	}
}
