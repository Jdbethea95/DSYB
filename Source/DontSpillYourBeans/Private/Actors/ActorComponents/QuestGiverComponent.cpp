// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ActorComponents/QuestGiverComponent.h"

// Sets default values for this component's properties
UQuestGiverComponent::UQuestGiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	MyQuestDetails = nullptr;
	MyBaseQuest = nullptr;
}

// Called when the game starts
void UQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	//Initalize Quest Details with saved values from data table.
	MyBaseQuest = LoadQuestInfo();
}

ABaseQuest* UQuestGiverComponent::GetQuest()
{
	return MyBaseQuest;
}

FQuestDetails* UQuestGiverComponent::GetQuestDetails()
{
	//Context can be used to get a row based off of the contents of the cell.
	//This is useful for when you row names are the same.
	//All of our row names are different, therefore we can leave the ContextString blank.

	const FString context;
	return QuestRowHandle.GetRow<FQuestDetails>(context);
}

ABaseQuest* UQuestGiverComponent::LoadQuestInfo()
{
	//Who owns this spawn?
	FActorSpawnParameters params;
	params.Instigator = GetOwner()->GetInstigator();
	params.Owner = GetOwner();

	//Setting Translation parameters
	FVector Location = GetOwner()->GetActorLocation();
	FRotator Rotation = GetOwner()->GetActorRotation();

	//Spawn Initial Reference to BaseQuest
	ABaseQuest* spawnedQuest = Cast<ABaseQuest>(GetWorld()->SpawnActor<ABaseQuest>(BaseQuestBase, Location, Rotation, params));

	if (!IsValid(spawnedQuest))
		return nullptr;

	//Set Quest Properties
	spawnedQuest->QuestID = QuestRowHandle.RowName;
	spawnedQuest->QuestDetails = GetQuestDetails();

	return spawnedQuest;
}
