// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/RaceNPC.h"
#include "FoxNPC.generated.h"

class APatrolPoint;
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API AFoxNPC : public ARaceNPC
{
	GENERATED_BODY()

public:
	AFoxNPC();

	FVector GetNextPoint() override;

protected:
	virtual void BeginPlay() override;
	virtual void OnInteract() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
		FName GrabObject;


		virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
