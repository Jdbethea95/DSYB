// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controllers/BaseAIController.h"
#include "Perception/AIPerceptionSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawn/BaseCharacter.h"

ABaseAIController::ABaseAIController()
{
	//Basic AI Setup, Turns on tick to update ai and sets a delegate to be called upon each perception update to detect player.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	AIPerceComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	AIPerceComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::DetectPlayerAction);

	//UE_LOG(LogTemp, Warning, TEXT("AI created")); //test was successful
}

//On AI possession Run the Associated BehaviorTree. BehaviorTree Assigned In blueprint.
void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(AIBehaviorTree);
	//UE_LOG(LogTemp, Warning, TEXT("AI Possessed")); //test was successful
}

void ABaseAIController::DetectPlayerAction(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* Board = GetBlackboardComponent();
	//UE_LOG(LogTemp, Warning, TEXT("DetectPlayerAction Ran")); //Test was successful

	//A Cast to see if the Actor is A Player, might change on player class we end with.
	ABaseCharacter* player = Cast<ABaseCharacter>(Actor);

	if (!IsValid(player))
		return;

	//detect if the player is present or not within the AI's range
	if (Stimulus.WasSuccessfullySensed())
	{
		Board->SetValueAsObject("Player", Actor);
		SetGuardLocation();
		//UE_LOG(LogTemp, Warning, TEXT("AI Detected Player")); //test was successful
	}
	else
	{
		Board->ClearValue(FName("Player"));
		ClearGuardLocation();
		//UE_LOG(LogTemp, Warning, TEXT("Player Dropped")); //test was successful
	}
}

void ABaseAIController::SetGuardLocation()
{
	UBlackboardComponent* Board = GetBlackboardComponent();

	if (IsValid(Board))
		Board->SetValueAsVector("GuardPoint", SavePoint);
}

void ABaseAIController::SaveGuardLocation(FVector location)
{
	SavePoint = location;
}

void ABaseAIController::ClearGuardLocation()
{
	UBlackboardComponent* Board = GetBlackboardComponent();

	if (IsValid(Board))
		Board->ClearValue("GuardPoint");
}
