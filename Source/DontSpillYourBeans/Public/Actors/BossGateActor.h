// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseGateActor.h"
#include "BossGateActor.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API ABossGateActor : public ABaseGateActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	ABossGateActor();
	//SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport|SFX")
	class USoundBase* AmbientSound;
	//map
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	int32 MapIndex;

	//bean 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	int32 BeanAmountToPass = 0;

	UFUNCTION(BlueprintCallable)
	bool CheckBeanCount(int beanCount);

	//colider

	void HandleGateInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
