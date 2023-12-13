// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HurtEnd.h"

void UHurtEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	animGraph = Cast<UEggyAnimEventGraph>(MeshComp->GetAnimInstance());
	//UE_LOG(LogTemp, Warning, TEXT("AIHurt hit"));
	if (IsValid(animGraph))
	{
		animGraph->DeactivateHurt();
		//UE_LOG(LogTemp, Warning, TEXT("AI Hurt done"));
	}
}
