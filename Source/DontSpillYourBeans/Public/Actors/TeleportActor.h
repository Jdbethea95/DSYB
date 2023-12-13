// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportActor.generated.h"

class APatrolPoint;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTeleportSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTeleportTwoParms, ATeleportActor*, pad, int, id);

UCLASS()
class DONTSPILLYOURBEANS_API ATeleportActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportActor();

	bool bJustPorted;
	bool bisUnlocked;
	int PortalID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FText Title;

	FTeleportTwoParms OnActivate;
	FTeleportSignature OnDeactivate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportal")
		ATeleportActor* OtherTeleportal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportal")
		APatrolPoint* TelePoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportal")
		bool bUsePoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABaseCharacter* player;

	UFUNCTION()
		virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetDestination(ATeleportActor* DestinationPortal);
	virtual void TeleportPlayer();
};
