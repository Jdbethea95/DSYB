// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ComboStart.h"

void UComboStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
	
	Player->TimerBegin();
}
