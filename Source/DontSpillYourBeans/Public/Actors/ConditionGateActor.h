// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BossGateActor.h"
#include "ConditionGateActor.generated.h"

class ABaseAICharacter;
class ACheckPoint;


/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API AConditionGateActor : public ABossGateActor
{
	GENERATED_BODY()

//protected variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition Toggles")
		bool bEnemyCondition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition Toggles")
		bool bItemCondition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition Toggles")
		bool bLocationCondition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* MeshComponent;

public:
	AConditionGateActor();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition Parameters")
	ABaseAICharacter* EnemyTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition Parameters")
		TSubclassOf<ACheckPoint> LocationTarget;

	UFUNCTION()
		void ActiveGateOnEnemy(int num);

	//protected functions
protected:
	void BeginPlay() override;


	void ActivateGate();
	void DeactivateGate();

	void COND_Check();
	
};
