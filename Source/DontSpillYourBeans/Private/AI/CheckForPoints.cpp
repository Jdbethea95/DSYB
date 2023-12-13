// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CheckForPoints.h"
#include "AI/Controllers/BaseAIController.h"
#include "Actors/RaceNPC.h"

EBTNodeResult::Type UCheckForPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* aiController = OwnerComp.GetAIOwner();
	if (aiController == nullptr)
	{

		//UE_LOG(LogTemp, Error, TEXT("Controller FAILURE"));
		return EBTNodeResult::Failed;
	}


	APawn* aiPawn = aiController->GetPawn();
	if (aiPawn == nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("PAWN FAILURE"));
		return EBTNodeResult::Failed;
	}


	ARaceNPC* enemy = Cast<ARaceNPC>(aiPawn);
	if (!IsValid(enemy))
	{
		//UE_LOG(LogTemp, Error, TEXT("Character FAILURE"));
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* blkBrd = OwnerComp.GetBlackboardComponent();
	if (blkBrd == nullptr)
	{

		//UE_LOG(LogTemp, Error, TEXT("Baord FAILURE"));
		return EBTNodeResult::Failed;
	}

	if (enemy->ReachedLastPoint())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
}
