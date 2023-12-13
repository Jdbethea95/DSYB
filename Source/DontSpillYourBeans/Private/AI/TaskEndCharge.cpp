// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskEndCharge.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"
#include "AI/Characters/ChargeAIBoss.h"

EBTNodeResult::Type UTaskEndCharge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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


	AChargeAIBoss* enemy = Cast<AChargeAIBoss>(aiPawn);
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


	blkBrd->ClearValue(FName("TargetLocation"));
	blkBrd->ClearValue(FName("CanCharge"));

	enemy->EndAttackCall();

	if (enemy->CanPhaseTwo())
	{
		//blkBrd->SetValueAsBool(FName("NextPhase"), true);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UTaskEndCharge::UTaskEndCharge()
{
	NodeName = TEXT("End Charge");
}
