// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TaskFindPoint.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UTaskFindPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UTaskFindPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector DestinationKey;
};
