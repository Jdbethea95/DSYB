// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveFilesSaveGame.generated.h"

/**
 * 
 * This is a save used to save a list of all save profile names
 */
UCLASS()
class DONTSPILLYOURBEANS_API USaveFilesSaveGame : public USaveGame
{
	GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		FString SaveFilesName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		TArray<FString> SaveNames;
	//Used for 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int32 LastActiveSave;

	
	USaveFilesSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool RemoveSaveFile(FString SaveToRemove);
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool AddSaveFile(FString  SaveSlotToAdd);
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool CheckifSaveExists();
	UFUNCTION(BlueprintCallable, Category = "Saving")
	int32 GetSaveIndex(FString SaveToGet);
	UFUNCTION(BlueprintCallable, Category = "Saving")
	FString GetLastActiveSave();
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool Save();
	UFUNCTION(BlueprintCallable, Category = "Saving")
	USaveFilesSaveGame* LoadSavesFileData();

};
