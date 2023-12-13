// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Containers/Map.h"
#include "MyGameInstance.generated.h"
USTRUCT(BlueprintType) struct FSaveInfo 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavingInfo")
		FString  currentSaveSlot = FString(TEXT("None"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavingInfo")
	int32  currentSaveIndex;
  // used to hold current save when deleting 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavingInfo")
	int32  SelectedSaveIndex;


	/// <summary>
	/// if there are save files
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavingInfo")
	bool saveFilesExist = false;
	/// <summary>
	/// used to disable the ablity to save 
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavingInfo")
	bool canSaveNow = true;

	/// <summary>
	/// save file taht contains save file names
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavingInfo|Save file Data")
	class USaveFilesSaveGame* savesData;
	/// <summary>
	/// current save file that was loaded
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavingInfo|Save file Data")
	class USaveDataSaveGame* playerSavedata;

	//  save file type for level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavingInfo|Save file Data")
	class USaveLevelSaveGame* levelSavedata;

	FSaveInfo& FSaveInfo::operator =(const FSaveInfo& other)
	{
		currentSaveSlot  = other.currentSaveSlot;
		currentSaveIndex = other.currentSaveIndex;
		saveFilesExist   = other.saveFilesExist;
		return *this;
	}

};
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable)
		void QuitGame();

#pragma region Functions Debug

	UFUNCTION(BlueprintCallable)
		void ToggleIsDebugTrue();

	UFUNCTION(BlueprintCallable)
		void SetisDebugTrue(bool input);

	UFUNCTION(BlueprintCallable)
		bool GetisDebugTrue();
private:
	UPROPERTY()
		bool isDebugTrue;
#pragma endregion
#pragma region Saving and Loading
#pragma region Save Info
public :
	//The save file that has a list of all saves associated with one save name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		FSaveInfo savingData;
	//called to load save files data
// called in main menu when game starts

	/// <summary>
	/// Loads the save file containg the list of player save files
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
		bool  LoadSavesFileData();
	/// <summary>
	/// makes a new save and sets the default save information
	/// </summary>
	/// <param name="SaveSlot"></param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
		bool  MakeNewSave(FString SaveSlot);

		UFUNCTION(BlueprintCallable)
		bool  LoadSaveData(FString SaveSlot);

		/// <summary>
		/// Deletes save in slot and resets the save infow on the gaminstance 
		/// if needed when the curent save is deleted
		/// when current save is deleted it loadsmain menu map
		/// </summary>
		/// <param name="SaveSlot"></param>
		/// <returns></returns>
		UFUNCTION(BlueprintCallable)
		bool  DeleteSaveData(FString SaveSlot);

		UFUNCTION(BlueprintCallable)
		void  LoadCurrentSaveData();

		UFUNCTION(BlueprintCallable)
		void  DeleteCurrentSaveData();

		//player saving
		UFUNCTION(BlueprintCallable)
		bool  SaveAllData();
		

		/// <summary>
		/// This functions saves player information to current active savedata
		/// </summary>
		/// <returns></returns>
		UFUNCTION(BlueprintCallable)
		bool  SavePlayerData(class AInventoryPlayer* player);

		/// <summary>
		/// this functions loads the current save files data into the player
		/// </summary>
		UFUNCTION(BlueprintCallable)
		void LoadPlayerSaveData(class AInventoryPlayer* player);

		UFUNCTION(BlueprintCallable)
		void ClearSaveInfo();
		//level saving
		UFUNCTION(BlueprintCallable, Category = "Saving")
		bool  SaveLevelData();

		UFUNCTION(BlueprintCallable, Category = "Saving")
		int32 LoadLevelSaveData();
		/// <summary>
		/// Level Progression manager
		/// </summary>
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GM|Level Progression")
		class AItemManager* itemManager;

		/// <summary>
		/// called to load a players savefiles and loads them to the hub world
		/// </summary>
		/// <param name="saveIndex"></param>
		UFUNCTION(BlueprintCallable)
		void LoadGame(int32 saveIndex);

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LoadingMap")
		int32 saveLimit = 3;

		UFUNCTION(BlueprintCallable)
		bool  SavePlayerWardrobeData(class ABaseCharacter* player);

		UFUNCTION(BlueprintCallable)
		void  LoadPlayerWardrobeData(class AInventoryPlayer* player);

		UFUNCTION(BlueprintCallable)
		void  DeleteAllSaves();
#pragma endregion
#pragma endregion
#pragma region Loading to another Map
public:
	UFUNCTION(BlueprintCallable, Category = "LoadingMap")
		void LoadMainMenu();

	UFUNCTION(BlueprintCallable, Category = "LoadingMap")
		void LoadMapTutorial();

	UFUNCTION(BlueprintCallable, Category = "LoadingMap")
		void LoadMapHUB();

		UFUNCTION(BlueprintCallable, Category = "LoadingMap")
		void LoadCharacterMap();

	UFUNCTION(BlueprintCallable, Category = "LoadingMap")
		void LoadMapFirstLevel();

	UFUNCTION(BlueprintCallable, Category = "LoadingMap")
		void LoadCurrentMap();

	UFUNCTION(BlueprintCallable, Category = "LoadingMap")
		bool CheckIfValidMapIndex(int32 MapIndex);

		////////////////////
		//MA INDEX RELATED
		/////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingMap|Indexs")
		TArray<FName> Maps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingMap|Indexs")
	int32 CurrentLevelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingMap|Indexs")
	int32 TutorialIndex;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingMap|Indexs")
		int32 MainMenuIndex;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingMap|Indexs")
		int32 HubIndex;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingMap|Indexs")
		int32 FirstLevelIndex;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingMap|Indexs")
		int32 CharMakerMap;

	UFUNCTION(BlueprintCallable)
		void LoadMapSafe(int32 MapIndex);


private:


	

#pragma endregion
#pragma region LoadingScreen
public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Loading")
	class UUserWidget* LoadingScreenRef;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Loading")
		TSubclassOf<class UUserWidget> LoadingScreenClass;

		UFUNCTION(BlueprintCallable)
		void ShowLoadingScreen();

		UFUNCTION(BlueprintCallable)
		void RemoveLoadingScreen();


#pragma endregion
#pragma region saving indicator
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Saving")
		class UUserWidget* SavingIndicatorRef;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Saving")
		TSubclassOf<class UUserWidget> SavingIndicatorClass;

		UFUNCTION(BlueprintCallable)
		void ShowSavingIndicator();

		UFUNCTION(BlueprintCallable)
		void RemoveSavingIndicator();

#pragma endregion



};
