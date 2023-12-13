// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TaskFindGuardPoint.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UTaskFindGuardPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UTaskFindGuardPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector DestinationKey;
};
