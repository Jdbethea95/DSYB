// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseQuest.h"

// Sets default values
ABaseQuest::ABaseQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	QuestID = "";

	QuestDetails = FQuestDetails();

	CurrentStage = 0;

	CurrentDialog = 0;

	CurrentStageDetails = FStageDetails();

	CurrentObjectiveProgress = TMap<FString, int>();

	bIsComplete = false;

	bIsAccepted = false;

	bIsKnown = false;

	bIsTracked = false;

}

// Called when the game starts or when spawned
void ABaseQuest::BeginPlay()
{
	Super::BeginPlay();
	
}
