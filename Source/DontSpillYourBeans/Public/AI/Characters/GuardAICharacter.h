// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Characters/BaseAICharacter.h"
#include "GuardAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API AGuardAICharacter : public ABaseAICharacter
{
	GENERATED_BODY()

public:
	AGuardAICharacter();

	virtual bool AttackCall() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float GetDirection();

	FVector GuardPointLocation;

public:
	FVector GetGuardPoint();
};
