// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Actors/BaseQuest.h"
#include "QuestGiverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DONTSPILLYOURBEANS_API UQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestGiverComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table Details", DisplayName = "Quest")
		FDataTableRowHandle QuestRowHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Classes");
		TSubclassOf<ABaseQuest> BaseQuestBase;

	//Send Quest Details to containing Actor to give to interacting Player
	ABaseQuest* GetQuest();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FQuestDetails* GetQuestDetails();

	ABaseQuest* LoadQuestInfo();

	ABaseQuest* MyBaseQuest;
	FQuestDetails* MyQuestDetails;
};
