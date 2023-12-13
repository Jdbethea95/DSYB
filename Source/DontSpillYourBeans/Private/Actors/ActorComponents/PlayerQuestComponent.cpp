// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/ActorComponents/PlayerQuestComponent.h"
#include "Pawn/InventoryPlayer.h"

// Sets default values for this component's properties
UPlayerQuestComponent::UPlayerQuestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}

// Called when the game starts
void UPlayerQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	//Load from saved quests
	LoadCurrentQuests();

}

bool UPlayerQuestComponent::QueryActiveQuest(ABaseQuest* Quest)
{
	return CurrentActiveQuests.Contains(Quest->QuestID);
}

bool UPlayerQuestComponent::AddNewQuest(ABaseQuest* Quest)
{
	if (!IsValid(Quest) || !IsValid(this))
		return false;

	//Add the quest if it hasn't already been added.
	if (INDEX_NONE == CurrentActiveQuests.AddUnique(Quest->QuestID))
		return false;

	CurrentActiveQuests;

	//If current quests is emtpy start quest system tutorial
	if (CurrentQuests.IsEmpty())
	{
		//do quest tutorial stuff
	}

	//AddUnique returns INDEX_NONE if spawnedQuest already exists inside of the array.
	if (INDEX_NONE == CurrentQuests.AddUnique(Quest))
		return false;

	CurrentQuests;

	return true;
}

APlayerController* UPlayerQuestComponent::GetPlayerController()
{
	return GetWorld()->GetFirstPlayerController<APlayerController>();;
}

void UPlayerQuestComponent::LoadCurrentQuests()
{
	if (!IsValid(this))
		return;

	//CurrentQuests = something;
}

