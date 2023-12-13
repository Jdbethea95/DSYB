// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskFindGuardPoint.h"
#include "AI/Controllers/BaseAIController.h"
#include "AI/Characters/GuardAICharacter.h"

EBTNodeResult::Type UTaskFindGuardPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	
	ABaseAIController* enemy = Cast<ABaseAIController>(aiController->GetOwner());
	if (IsValid(enemy))
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

	

	enemy->SetGuardLocation();

	//UE_LOG(LogTemp, Warning, TEXT("I WAS SUCCESSFUL! %s"), *Location.Location.ToString());
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UTaskFindGuardPoint::UTaskFindGuardPoint()
{
	NodeName = TEXT("Find Guard Point");
}
