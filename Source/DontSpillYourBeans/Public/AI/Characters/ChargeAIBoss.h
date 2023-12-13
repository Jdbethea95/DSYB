// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Characters/BaseAICharacter.h"
#include "ChargeAIBoss.generated.h"


/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API AChargeAIBoss : public ABaseAICharacter
{
	GENERATED_BODY()
	

public:
	AChargeAIBoss();

	virtual bool AttackCall() override;
	virtual bool EndAttackCall() override;

	virtual bool SpecialActionCall();
	virtual bool CanPhaseTwo();
	virtual bool CurrentCharging();

	FVector GetHomeLocation();

protected:

	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;



	bool IsCharging;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float ChargeSpeedMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float AccelMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		TArray<class USoundBase*> EnemySounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		class USoundBase* ValidSound;

	bool PlayEnemyCall(USoundBase* sound);

private:
	bool ChargePlayer;
	FVector HomeLocation;
	float WalkSpeed;
	float UnitAccel;

};
