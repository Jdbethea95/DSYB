// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwordActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerAttack);

UCLASS()
class DONTSPILLYOURBEANS_API ASwordActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwordActor();

	FOnPlayerAttack OnPlayerAttack;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	/// <summary>
	/// Sets Sword Objects Damage to be dealt upon Collision
	/// </summary>
	/// <param name="Damage"> - assigned to Sword Damage.</param>
	void SetSwordDamage(float Damage);

	/// <summary>
	/// Activates Sword's Collider to detect collision
	/// </summary>
	void ActivateSword();

	void SetSwordOwner(AActor* owner);

	AActor* GetSwordOwner();

	int PassOnValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAudioComponent* StereoSystem;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AActor* SwordOwner;

	float SwordDamage;
	bool isSwinging;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		TArray<class USoundBase*> WhackSounds;

	bool PlayWhackCall(USoundBase* sound);

public:	
	UFUNCTION()
		void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SwingSword();
	void StopSword();

};
