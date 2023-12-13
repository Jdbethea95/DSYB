// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	ABaseAIController();
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Behavior")
		UBehaviorTree* AIBehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior")
		UAIPerceptionComponent* AIPerceComponent;

	UFUNCTION()
		void DetectPlayerAction(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
		void SetGuardLocation();

	UFUNCTION()
		void SaveGuardLocation(FVector location);

	UFUNCTION()
		void ClearGuardLocation();

private:
	FVector SavePoint;
		
};
