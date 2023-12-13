// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ConditionGateActor.h"
#include "AI/Characters/BaseAICharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Actors/CheckPoint.h"



AConditionGateActor::AConditionGateActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
}


void AConditionGateActor::ActiveGateOnEnemy(int num)
{
	ActivateGate();
}

void AConditionGateActor::BeginPlay()
{
	Super::BeginPlay();

	BeanAmountToPass = 0;
	DeactivateGate();
	COND_Check();
}

void AConditionGateActor::ActivateGate()
{
	MeshComponent->SetVisibility(true);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AConditionGateActor::DeactivateGate()
{
	MeshComponent->SetVisibility(false);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AConditionGateActor::COND_Check()
{
	if (bEnemyCondition)
	{
		if (IsValid(EnemyTarget))
		{
			EnemyTarget->OnAIDeath.AddDynamic(this, &AConditionGateActor::ActiveGateOnEnemy);
		}

		return;
	}

	if (bLocationCondition)
	{

		if (IsValid(LocationTarget))
		{

		}

		return;
	}

	if (bItemCondition)
	{
		BeanAmountToPass = 1;
		return;
	}
}
