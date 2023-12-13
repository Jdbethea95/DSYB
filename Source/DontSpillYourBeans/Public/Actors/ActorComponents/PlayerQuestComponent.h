// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/BaseQuest.h"
#include "PlayerQuestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DONTSPILLYOURBEANS_API UPlayerQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerQuestComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		TArray<FName> CurrentActiveQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		TArray<FName> CompletedQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		TArray<FName> TrackedQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		TArray<ABaseQuest*> CurrentQuests;
	
	bool AddNewQuest(ABaseQuest* Quest);

	//Function can be pure for optimization.
	//Pure function is not changing any values just reporting based off of a value.

	//Is the questID already present in the ActiveQuest Array?
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool QueryActiveQuest(ABaseQuest* Quest);

	APlayerController* GetPlayerController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void LoadCurrentQuests();
};
