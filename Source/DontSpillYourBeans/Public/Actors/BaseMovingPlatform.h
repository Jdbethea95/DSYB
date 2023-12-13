// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMovingPlatform.generated.h"

USTRUCT(BlueprintType)
struct FMovementDirection
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float xMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float yMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float zMovement;
};

UCLASS()
class DONTSPILLYOURBEANS_API ABaseMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseMovingPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		FMovementDirection MovementDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float DelayTime;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool Toggle;
	FVector StartLoc;
	FVector EndLoc;
	float MovementSpeed;
	float CurrTime;

	bool delayToggle;
	bool HandleCheck;

	void MovePlatform(float DeltaTime);

};
