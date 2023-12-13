// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemManager.generated.h"

class APickupObjectShell;


UCLASS()
class DONTSPILLYOURBEANS_API AItemManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemManager();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Array")
		TArray<APickupObjectShell*> pickupList;

	TArray<int> CollectedList;
	bool IsShellSet;
	int IDIncrement;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<int> GetItemStates();
	void SetItemStates(TArray<int> UpdatedList);

	UFUNCTION()
		void UpdateCollectedList(int pickupID);

	void SetUpPickShells();

	UFUNCTION()
		void CheckInShell(APickupObjectShell* object);

};
