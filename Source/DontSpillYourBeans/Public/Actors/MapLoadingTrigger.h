// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapLoadingTrigger.generated.h"

UCLASS()
class DONTSPILLYOURBEANS_API AMapLoadingTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AMapLoadingTrigger();
	UFUNCTION(BlueprintCallable)
	void HandleTelport(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	class 	UMyGameInstance* GamesInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger|Colider")
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger|Teleport")
	int32 MapIndex = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger|Teleport|SFX")
	class USoundBase* InvalidSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger|Teleport|SFX")
	class USoundBase* ValidSound;

	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* sound);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
