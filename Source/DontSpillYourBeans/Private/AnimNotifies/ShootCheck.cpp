// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ShootCheck.h"

void UShootCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AFlyingAICharacter* Enemy = Cast<AFlyingAICharacter>(MeshComp->GetOwner());

	if (IsValid(Enemy))
	{
		if (!Enemy->CanShoot() || Enemy->GetLandToggle())
		{
			Enemy->EndAttackCall();
			UE_LOG(LogTemp, Warning, TEXT("EndAttackCALL~!"));
		}
			
	}
}
