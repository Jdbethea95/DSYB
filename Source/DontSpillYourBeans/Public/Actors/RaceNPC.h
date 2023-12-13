// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/QuestNPC.h"
//#include "Actors/BaseNPC.h"
#include "RaceNPC.generated.h"


class APatrolPoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRaceSignature);
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API ARaceNPC : public AQuestNPC
{
	GENERATED_BODY()
	
public:
	ARaceNPC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Racer")
	TArray<APatrolPoint*> Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Racer")
		int MaxLaps;

	virtual FVector GetNextPoint();

	virtual void AcceptQuest() override;

	virtual bool ReachedLastPoint();

	bool IsRacerReady;
	bool IsRacerFinished;
	FVector HomeLocation;
	FRaceSignature OnReady;
protected:
	virtual void BeginPlay() override;
	virtual void OnInteract() override;

	int CurrentLap;
	int CurrentPoint;
	bool IsLap;
};
