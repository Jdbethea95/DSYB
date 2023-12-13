// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "BaseQuest.generated.h"

UENUM(BlueprintType)
enum EObjectiveTypes
{
	OT_LOCATION UMETA(DisplayName = "Location"),
	OT_KILL UMETA(DisplayName = "Kill"),
	OT_INTERACT UMETA(DisplayName = "Interact"),
	OT_COLLECT UMETA(DisplayName = "Collects"),
	OT_DEFAULT UMETA(DispalyName = "Default")
};

USTRUCT(BlueprintType) 
struct FObjectiveDetails
{
	GENERATED_BODY()

public:

	//Name of stage to be displayed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Details")
		FText ObjectiveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Details")
		FText FullDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Details")
		TEnumAsByte<EObjectiveTypes> ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Details")
		FString ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Details")
		int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective Details")
		bool IsOptional;

	FObjectiveDetails()
	{
		ObjectiveName = FText();

		FullDescription = FText();

		ObjectiveType = EObjectiveTypes::OT_DEFAULT;

		ObjectiveID = "";

		Quantity = 0;

		IsOptional = false;
	}

	FObjectiveDetails& FObjectiveDetails::operator =(const FObjectiveDetails& other)
	{
		ObjectiveName = other.ObjectiveName;
		FullDescription = other.FullDescription;
		ObjectiveType = other.ObjectiveType;
		ObjectiveID = other.ObjectiveID;
		Quantity = other.Quantity;
		IsOptional = other.IsOptional;

		return *this;
	}
};

USTRUCT(BlueprintType) 
struct FStageDetails
{
	GENERATED_BODY()

public:

	//Name of stage to be displayed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Details")
		FText StageName;									
															
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Details")
		FText FullDescription;
															
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Details")
		TArray<FObjectiveDetails> Objectives;
															
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Details")
		int GemRewardCount;	

	FStageDetails()
	{
		StageName = FText();

		FullDescription = FText();

		Objectives = TArray<FObjectiveDetails>();

		GemRewardCount = 0;
	}

	FStageDetails& FStageDetails::operator =(const FStageDetails& other)
	{
		StageName = other.StageName;
		FullDescription = other.FullDescription;
		Objectives = other.Objectives;
		GemRewardCount = other.GemRewardCount;

		return *this;
	}
};

USTRUCT(BlueprintType) 
struct FQuestDetails : public FTableRowBase
{
	GENERATED_BODY()

public:

	//Name of quest to be displayed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Details")
		FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Details")
		FText FullDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Details")
		FText TrackerDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Details")
		bool isMainQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Details", DisplayName = "Pre-Quest Dialog")
		TArray<FText> PreQuestDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Details")
		TArray<FStageDetails> Stages;

	FQuestDetails()
	{
		QuestName = FText();

		FullDescription = FText();

		TrackerDescription = FText();

		isMainQuest = true;

		PreQuestDialog = TArray<FText>();

		Stages = TArray<FStageDetails>();
	}

	FQuestDetails& FQuestDetails::operator =(const FQuestDetails& other)
	{
		QuestName = other.QuestName;
		FullDescription = other.FullDescription;
		TrackerDescription = other.TrackerDescription;
		isMainQuest = other.isMainQuest;
		PreQuestDialog = other.PreQuestDialog;
		Stages = other.Stages;

		return *this;
	}

	FQuestDetails& FQuestDetails::operator =(FQuestDetails* other)
	{
		QuestName = other->QuestName;
		FullDescription = other->FullDescription;
		TrackerDescription = other->TrackerDescription;
		isMainQuest = other->isMainQuest;
		PreQuestDialog = other->PreQuestDialog;
		Stages = other->Stages;

		return *this;
	}
};

UCLASS()
class DONTSPILLYOURBEANS_API ABaseQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	
	ABaseQuest();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info", meta = (ExposeOnSpawn = true))
		FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		FQuestDetails QuestDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		int CurrentStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		int CurrentDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		FStageDetails CurrentStageDetails;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		TMap<FString, int> CurrentObjectiveProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		bool bIsComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		bool bIsAccepted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		bool bIsKnown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
		bool bIsTracked;

	/*ABaseQuest& ABaseQuest::operator =(ABaseQuest* other)
	{
		QuestID = other->QuestID;
		QuestDetails = other->QuestDetails;
		CurrentStage = other->CurrentStage;
		CurrentDialog = other->CurrentDialog;
		CurrentStageDetails = other->CurrentStageDetails;
		CurrentObjectiveProgress = other->CurrentObjectiveProgress;
		bIsComplete = other->bIsComplete;
		bIsAccepted = other->bIsAccepted;
		bIsKnown = other->bIsKnown;
		bIsTracked = other->bIsTracked;

		return *this;
	}

	ABaseQuest& ABaseQuest::operator =(const ABaseQuest& other)
	{
		QuestID = other.QuestID;
		QuestDetails = other.QuestDetails;
		CurrentStage = other.CurrentStage;
		CurrentDialog = other.CurrentDialog;
		CurrentStageDetails = other.CurrentStageDetails;
		CurrentObjectiveProgress = other.CurrentObjectiveProgress;
		bIsComplete = other.bIsComplete;
		bIsAccepted = other.bIsAccepted;
		bIsKnown = other.bIsKnown;
		bIsTracked = other.bIsTracked;

		return *this;
	}*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
