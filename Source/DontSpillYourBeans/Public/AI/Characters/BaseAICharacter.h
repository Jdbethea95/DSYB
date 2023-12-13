// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Utility/EggyAnimEventGraph.h"
#include "Components/SphereComponent.h"
#include "BaseAICharacter.generated.h"

class AItemProjectile;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, int, Count);

UCLASS()
class DONTSPILLYOURBEANS_API ABaseAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAICharacter();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		class UEggyAnimEventGraph* AnimGraph;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAudioComponent* StereoSystem;

	FOnDeath OnAIDeath;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

#pragma region EnemyStats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float Pushbackstrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float UnitMaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float UnitMovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float TrailZSpawn;

	//Drop Chance 0.01 - 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	float DropChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats");
	TSubclassOf<AItemProjectile> ItemTrail;

#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* SphereComponent;

	FVector PushbackVector;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Attack

	virtual bool AttackCall();

	virtual bool EndAttackCall();

	virtual bool EnemySetup(float Damage, float Health, float Speed, float Pushback);

#pragma endregion

#pragma region Death

	virtual bool KillEnemy();
	virtual bool IsAlive();
	virtual bool DropItem();

#pragma endregion


protected:
	UFUNCTION()
		virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	bool IsInRange;
	bool IsDead;
	float UnitHealth;

#pragma region Audio

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		TArray<USoundBase*> AttackAudios;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		TArray<USoundBase*> HurtAudios;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		TArray<USoundBase*> MovementAudios; //in an array in case we need a couple of sounds to play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		USoundBase* DeathAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		USoundBase* CallAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		bool PlaySoundOnHit;

#pragma endregion

public:

#pragma region AudioFunctions

	//Audio Functions
	void PlayAttackAudio();
	void PlayHurtAudio();
	void PlayDeathAudio();
	void PlayCallAudio();
	void PlayMovementAudio();

#pragma endregion

};
