// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskFindChargeLine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"
#include "AI/Characters/BaseAICharacter.h"
#include "Pawn/BaseCharacter.h"

EBTNodeResult::Type UTaskFindChargeLine::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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


	ABaseAICharacter* enemy = Cast<ABaseAICharacter>(aiPawn);
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

	
	ABaseCharacter* player = Cast<ABaseCharacter>(blkBrd->GetValueAsObject(FName("Player")));

	if (!IsValid(player))
	{
		//UE_LOG(LogTemp, Error, TEXT("player FAILURE"));
		return EBTNodeResult::Failed;
	}

	FVector Target = player->GetActorLocation();

	blkBrd->SetValueAsVector(FName("TargetLocation"), Target);
	//UE_LOG(LogTemp, Warning, TEXT("charge is true"));
	blkBrd->SetValueAsBool(FName("CanCharge"), true);

	enemy->AttackCall();

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UTaskFindChargeLine::UTaskFindChargeLine()
{
	NodeName = TEXT("Set Charge");
}
