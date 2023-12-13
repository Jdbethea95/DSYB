// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/PlayerAnimGraph.h"


void UPlayerAnimGraph::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	APawn* Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
		Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
	}
}

bool UPlayerAnimGraph::getAttacking()
{
	return isAttacking;
}

void UPlayerAnimGraph::setAttacking(bool Attacking)
{
	isAttacking = Attacking;
}

void UPlayerAnimGraph::PlayAttack()
{
	int Num = rand() % Attacks.Num();
	if (!IsPlayingSlotAnimation(Attacks[Num], FName("Action")))
	{
		PlaySlotAnimationAsDynamicMontage(Attacks[Num], FName("Action"));
	}
}

void UPlayerAnimGraph::PlayJump()
{
	if (!IsPlayingSlotAnimation(jumpSequence, FName("Action")))
	{
		PlaySlotAnimationAsDynamicMontage(jumpSequence, FName("Action"));
	}
}

void UPlayerAnimGraph::PlayHurt()
{
	if (!IsPlayingSlotAnimation(Damaged, FName("Action")))
	{
		PlaySlotAnimationAsDynamicMontage(Damaged, FName("Action"));
	}
}

void UPlayerAnimGraph::PlayDeath()
{
	isDeath = true;
}

bool UPlayerAnimGraph::GetJump()
{
	return isJumping;
}

void UPlayerAnimGraph::SetJump(bool Jumping)
{
	isJumping = Jumping;
}



