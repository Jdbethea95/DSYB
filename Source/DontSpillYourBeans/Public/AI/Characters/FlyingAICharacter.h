// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Characters/BaseAICharacter.h"
#include "FlyingAICharacter.generated.h"

/**
 *
 */
UCLASS()
class DONTSPILLYOURBEANS_API AFlyingAICharacter : public ABaseAICharacter
{
	GENERATED_BODY()

public:
	AFlyingAICharacter();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Class Ref")
		TSubclassOf<class ADamageProjectile> ProjectileRef;

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual bool AttackCall() override;
	virtual bool EndAttackCall() override;
	virtual bool CanShoot();
	virtual bool GetLandToggle();
	virtual bool GetShootToggle();

	bool Land(float alpha);
	bool Rise(float alpha);

protected:
	bool Bobble(float alpha, bool trigger = true);
	virtual bool Shoot();


	virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float FlyingOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float BobLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float BobSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float LandSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float LandedTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	int MaxShootCount;

private:
	float upper;
	float lower;
	float ArielPos;
	float LandedPos;

	//used for lerping positions with deltatime
	float alphaSum;
	float deltaSum;

	int ShootCount;
	float ShootDelay;

	//State Toggles
	bool bobbleToggle;
	bool ShootToggle;
	bool LandToggle;
};
