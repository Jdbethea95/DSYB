// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/CheckPoint.h"
#include "Actors/RaceNPC.h"
#include "RaceTrack.generated.h"

class ACheckPoint;
class ABaseCharacter;
class ARaceNPC;
class URaceWidget;

UCLASS()
class DONTSPILLYOURBEANS_API ARaceTrack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARaceTrack();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckPoints")
		int MaxLaps;

	int CurrentLap;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckPoints")
		TArray<ACheckPoint*> CheckPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckPoints")
		ARaceNPC* racer;


	UFUNCTION()
		void StartRace();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URaceWidget* WC_RaceWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool IsLap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<URaceWidget> TSub_Widget;


	UFUNCTION()
		void UpdateCheckPoints(int ID, ABaseCharacter* player);

	void ToggleCollision();

	UFUNCTION()
		void WidgetSetup();
};
