// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskAttack.h"
#include "AI/Characters/BaseAICharacter.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* aiController = OwnerComp.GetAIOwner();
	if (aiController == nullptr)
		return EBTNodeResult::Failed;

	APawn* aiPawn = aiController->GetPawn();
	if (aiPawn == nullptr)
		return EBTNodeResult::Failed;

	ABaseAICharacter* Enemy = Cast<ABaseAICharacter>(aiPawn);
	if (Enemy == nullptr)
		return EBTNodeResult::Failed;

	//Enemy->AttackCall();
	Enemy->AnimGraph->ActivateAttack();

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UTaskAttack::UTaskAttack()
{
	NodeName = TEXT("AI Attack");
}
