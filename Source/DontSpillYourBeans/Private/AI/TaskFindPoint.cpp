// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskFindPoint.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UTaskFindPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	FNavLocation Location;

	AAIController* aiController = OwnerComp.GetAIOwner();
	if (aiController == nullptr)
		return EBTNodeResult::Failed;

	APawn* aiPawn = aiController->GetPawn();
	if (aiPawn == nullptr)
		return EBTNodeResult::Failed;

	FVector Origins = aiPawn->GetActorLocation(); //Gets Pawn from controller and Gets the ActorLocation

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (navSystem == nullptr)
		return EBTNodeResult::Failed;

	UBlackboardComponent* blkBrd = OwnerComp.GetBlackboardComponent();
	if (blkBrd == nullptr)
		return EBTNodeResult::Failed;

	//Asset Assignment End
	if (navSystem->GetRandomPointInNavigableRadius(Origins, radius, Location))
	{
		blkBrd->SetValueAsVector(DestinationKey.SelectedKeyName, Location.Location);

		//UE_LOG(LogTemp, Warning, TEXT("I WAS SUCCESSFUL! %s"), *Location.Location.ToString());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else 
	{ 
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed; 
	}

}

UTaskFindPoint::UTaskFindPoint()
{
	NodeName = TEXT("Find Random Point");
	radius = 1000.0f;
	DestinationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UTaskFindPoint, DestinationKey));
}
