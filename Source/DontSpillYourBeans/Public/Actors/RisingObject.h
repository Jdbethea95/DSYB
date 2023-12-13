// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RisingObject.generated.h"

UCLASS()
class DONTSPILLYOURBEANS_API ARisingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARisingObject();


	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float zMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float DelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toggles")
		bool IsDestructable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toggles")
		bool CanPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toggles")
		bool CanEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* boxCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* MeshComp;
	bool DelayToggle;
	bool isColliding;

	void MovePlatform(float DeltaTime);

	UFUNCTION()
		virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector EndLoc;

};
