// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseGateActor.h"
#include "HubGate.generated.h"

UCLASS()
class DONTSPILLYOURBEANS_API AHubGate : public ABaseGateActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHubGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
		int32 BeanAmountToPass = 0;

	UFUNCTION(BlueprintCallable)
		bool CheckBeanCount(int beanCount);



	void HandleGateInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
