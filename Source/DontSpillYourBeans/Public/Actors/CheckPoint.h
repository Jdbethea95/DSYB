// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

class ABaseCharacter;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPointSignature, int, id, ABaseCharacter*, player);

UCLASS()
class DONTSPILLYOURBEANS_API ACheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ID")
	int CheckpointID;

	FCheckPointSignature OnCheckHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* BoxComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* GateMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		USoundBase* GateHitAudio;

public:
	UFUNCTION()
		void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ToggleGate(bool bIsVisible = false);

};
