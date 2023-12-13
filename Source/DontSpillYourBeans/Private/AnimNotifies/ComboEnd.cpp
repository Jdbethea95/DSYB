// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ComboEnd.h"

void UComboEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Player = Cast<ABaseCharacter>(MeshComp->GetOwner());

	Player->TimerEnd();
}
