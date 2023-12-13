// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveLevelSaveGame.generated.h"

class AActor;

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API USaveLevelSaveGame : public USaveGame
{
	GENERATED_BODY()
public :
	USaveLevelSaveGame();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
	FString SaveFilesName;
	/// <summary>
	/// used to actors that need to be destroyed when a level loads
	/// such as doors
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level State|Doors")
	TArray< AActor*> actorsToDestroy;
	/// <summary>
/// used to actors that need to be destroyed when a level loads
/// such as pickups 
/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level State|Item Array")
	TArray<int> CollectedListOfItems; 


	//Actors 
	UFUNCTION(BlueprintCallable, Category = "Loading")
	void DestroyLoadedPickups();

	UFUNCTION(BlueprintCallable, Category = "Loading")
	void AddDestroyed(AActor* destroyed);
	//Pickups 
	UFUNCTION(BlueprintCallable, Category = "Loading")
	TArray<int> LoadItemStates();

	UFUNCTION(BlueprintCallable, Category = "Loading")
	void SaveItemStates(TArray<int> ListOfItems);

	//General save function
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool Save();
};
