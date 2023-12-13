// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskLand.h"
#include "AI/Characters/FlyingAICharacter.h"

EBTNodeResult::Type UTaskLand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* aiController = OwnerComp.GetAIOwner();
	if (aiController == nullptr)
		return EBTNodeResult::Failed;

	APawn* aiPawn = aiController->GetPawn();
	if (aiPawn == nullptr)
		return EBTNodeResult::Failed;

	AFlyingAICharacter* Enemy = Cast<AFlyingAICharacter>(aiPawn);
	if (Enemy == nullptr)
		return EBTNodeResult::Failed;

	if (Enemy->GetLandToggle())
	{
		
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UTaskLand::UTaskLand()
{
}
