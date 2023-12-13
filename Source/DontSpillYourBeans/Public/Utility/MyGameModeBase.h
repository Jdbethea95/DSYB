// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class UDefeatWidget;
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyGameModeBase();
	//Level Progression
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GM|Level Progression")
	class AItemManager* itemManager;


#pragma region DEFEAT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GM|UI|Defeat")
	class UUserWidget* DefeatScreenRef;

	UDefeatWidget* PlayerDefeatWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GM|UI|Defeat")
	TSubclassOf<UDefeatWidget> DeafeatScreenClass;


	UFUNCTION(BlueprintCallable, Category = "GM|UI")
	void ShowDefeatScreen();

	UFUNCTION(BlueprintCallable, Category = "GM|UI")
	void RemoveDefeatScreen();

	UFUNCTION(BlueprintCallable, Category = "GM|Defeat")
	void Defeated();

	UFUNCTION()
		void RespawnPlayer();
#pragma endregion 

#pragma region SAVING/LOADING
	/// <summary>
	/// Contains Save files information
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GM|UI")
	class 	UMyGameInstance* GamesInstance;
	/// <summary>
	/// Levels save data
	/// has things like permently destroyed actors 
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GM|Loading|SavingInfo")
	class USaveLevelSaveGame* LevelData;
	/// <summary>
/// the name of the save of the levels save file
/// usually made up of "savefilename" + "Level name"
/// unless a new game then its "NONE" + " LEVEL name"
/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GM|Loading|SavingInfo")
	FString  LevelSaveSlotName;



#pragma region PICKUPS

#pragma endregion 
#pragma region Actors


	/// <summary>
	/// used to store the classes of actors that will have their destroy functions bound to 
	/// add actor to destroyed in the level save data
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GM|Loading|Level State")
	TArray<TSubclassOf<class AActor>> ActorClassesToSaveDestruction;

	/// <summary>
	/// Loads level state such as picked up beans and destryoed doors etc
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "GM|Loading")
	int32 LoadLevelSaveData();

	/// <summary>
	/// binds a actors ondestroy to addDestroyed
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "GM|Loading")
	void BindDestroyed(TSubclassOf<class AActor > ActorClass);
	/// <summary>
	/// binds the ondestroyed of  all the actors of the types in ActorClassesToSaveDestruction to adddestroyed()
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "GM|Loading")
	void BindAllDestroyable();
	/// <summary>
	/// Destroys all actors from the level data 
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "GM|Loading")
	void DestroyLoadedActors();

#pragma endregion 

#pragma region Player
	void SetUpPlayerDefeat();
#pragma endregion 
#pragma endregion 



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
