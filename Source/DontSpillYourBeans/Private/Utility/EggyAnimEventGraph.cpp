// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/EggyAnimEventGraph.h"

void UEggyAnimEventGraph::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	APawn* Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
	}
}


//These functions are used because of the odd nature of the animations.
	//The root bone is rotated on the wrong axis so they can not be slots.
		//Nodes are used in animation to rotate then blend each animation.
void UEggyAnimEventGraph::ActivateAttack()
{
	Attack = 1.f;
}

void UEggyAnimEventGraph::DeactivateAttack()
{
	Attack = 0.f;
}

void UEggyAnimEventGraph::ActivateHurt()
{
	DeactivateAttack(); //if attacking, end attack.
	Hurt = 1.0f;
}

void UEggyAnimEventGraph::DeactivateHurt()
{
	Hurt = 0.0f;
}

void UEggyAnimEventGraph::DeathState(bool isDead)
{
	Death = isDead;
}

void UEggyAnimEventGraph::PlaySpecialAction()
{
	if (!IsPlayingSlotAnimation(SpecialAction, FName("Action")))
	{
		PlaySlotAnimationAsDynamicMontage(SpecialAction, FName("Action"));
	}
}

bool UEggyAnimEventGraph::IsHurt()
{
	return (Hurt > 0);
}
