// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGateActor.generated.h"

UCLASS()
class DONTSPILLYOURBEANS_API ABaseGateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
	class 	UMyGameInstance* GamesInstance;
	//SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate|SFX")
	class USoundBase* InvalidSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate|SFX")
	class USoundBase* ValidSound;
	//Var


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
	bool isLocked;
	//colider

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gate|Colider")
	class UBoxComponent* BoxComponent;

	UFUNCTION(BlueprintCallable)
	virtual void HandleGateInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;
	//functions

	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* sound);
	UFUNCTION(BlueprintCallable)
	void LockedSound();

};
