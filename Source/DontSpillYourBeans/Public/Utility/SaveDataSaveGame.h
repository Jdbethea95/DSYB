// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveDataSaveGame.generated.h"

/**
 *
 */


/// <summary>
/// container for ints
/// </summary>
USTRUCT(BlueprintType) struct FArrayIntContainer
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
	TArray <int> held;

	bool CheckvalidSlotIndex(int Index)
	{
		if (Index < held.Num())
		{
			return true;
		}
		return false;
	}
	int GetSlot(int Index)
	{
		if(CheckvalidSlotIndex(Index))
		{
			return held[Index];
		}
		return -1;
	}
	bool SetSlot(int Index, int Amount)
	{
		if (CheckvalidSlotIndex(Index))
		{
			held[Index] = Amount;
			return true;
		}
		return false;
	}
	void AddNewSlot(int newVar)
	{
		held.Add(newVar);
	}
};
USTRUCT(BlueprintType) struct FArrayFNameContainer
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
	TArray <FName> held;

	bool CheckvalidSlotIndex(int Index)
	{
		if (Index < held.Num())
		{
			return true;
		}
		return false;
	}
	FName GetSlot(int Index)
	{
		if (CheckvalidSlotIndex(Index))
		{
			return held[Index];
		}
		FName failed = "Invalid Index For Fname";
		return failed;
	}
	bool SetSlot(int Index, FName name)
	{
		if (CheckvalidSlotIndex(Index))
		{
			held[Index] = name;
			return true;
		}
		return false;
	}
	void AddNewSlot(FName name)
	{
		held.Add(name);
	}
	bool Contains(FName name)
	{
		return held.Contains(name);
		
	}
	int32 FindSlotIndex(FName name)
	{
		return held.Find(name);
	}
};

USTRUCT(BlueprintType) struct FArraySlotsContainer
{
	GENERATED_BODY()
private:


	UPROPERTY()
	FArrayIntContainer amounts;
public:
	/// <summary>
	/// used for add item function
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
	FArrayFNameContainer itemID;


	bool CheckvalidSlotIndex(int index)
	{
		if (itemID.CheckvalidSlotIndex(index) && amounts.CheckvalidSlotIndex(index))
		{
			return true;
		}
		return false;
	}
	int32 GetSlotsAmount(int index)
	{
		if (CheckvalidSlotIndex(index))
		{
			return amounts.GetSlot(index);
		}
		return -1;
	}
	FName GetSlotNameID(int index)
	{
	
			if (itemID.CheckvalidSlotIndex(index))
			{
				return itemID.GetSlot(index);
			}
			FName failed = "Invalid Index For Fname";
			return failed;
		
	}
	bool SetSlotAmount(int32 index, int32 Amount)
	{

		if (amounts.CheckvalidSlotIndex(index))
		{
			amounts.SetSlot(index, Amount);
			UE_LOG(LogTemp, Warning, TEXT("Set slot %f Amount:   %.2f "), index, Amount);
				return true;
		}
	


		return false;
	}
	void AddNewSlot(FName nameID, int32 Amount)
	{

		itemID.AddNewSlot(nameID);
		amounts.AddNewSlot(Amount);
	}
	void RemoveSlot(int32 index)
	{
		itemID.held.RemoveAt(index);
		amounts.held.RemoveAt(index);
	}
	int32 Count()
	{
		return itemID.held.Num();
	}

	void SaveAllItems(FArraySlotsContainer& inventory)
	{
		for (size_t i = 0; i < inventory.Count(); i++)
		{
		
			int32 index = itemID.FindSlotIndex(inventory.GetSlotNameID(i));

			if (index != -1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Item Name ID :  Found , index : %d "),index);
				SetSlotAmount(index, inventory.GetSlotsAmount(i));
			}
			else
			{
				AddNewSlot(inventory.GetSlotNameID(i), inventory.GetSlotsAmount(i));
			}
	
		}


	}
};


USTRUCT(BlueprintType) struct FArrayFloatContainer
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
	TArray <float> held;

	bool CheckvalidSlotIndex(float Index)
	{
		if (Index < held.Num())
		{
			return true;
		}
		return false;
	}
	float GetSlot(int Index)
	{
		if (CheckvalidSlotIndex(Index))
		{
			return held[Index];
		}
		return -1;
	}
	bool SetSlot(int Index, float Amount)
	{
		if (CheckvalidSlotIndex(Index))
		{
			held[Index] = Amount;
			return true;
		}
		return false;
	}
	void AddNewSlot(float newVar)
	{
		held.Add(newVar);
	}
};
USTRUCT(BlueprintType) struct FArrayBoolContainer
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
	TArray <bool> held;

	bool CheckvalidSlotIndex(float Index)
	{
		if (Index < held.Num())
		{
			return true;
		}
		return false;
	}
	int GetSlot(int Index)
	{
		if (CheckvalidSlotIndex(Index))
		{
			if (held[Index])
			{
				return 1;
			 }
		}
		return -1;
	}
	bool SetSlot(int Index, bool Amount)
	{
		if (CheckvalidSlotIndex(Index))
		{
			held[Index] = Amount;
			return true;
		}
		return false;
	}
	void AddNewSlot(bool newVar)
	{

	  held.Add(newVar);
	
	}
};
#pragma region STRUCTS
USTRUCT(BlueprintType) struct FRange
{
	GENERATED_BODY()

public:
	int32 Start;
	int32 End;
};
USTRUCT(BlueprintType) struct FPlayerCollectablesInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
	FArraySlotsContainer items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
	FRange Currency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
	FRange buffs;

	//currency
	/// <summary>
	/// normal,magic
	/// </summary>
	int GetCurrency(int CurrencyIndex)
	{
		return 0;
	}
	/// <summary>
	/// normal,magic
	/// </summary>
	void SetCurrency(int CurrencyIndex, int Amount)
	{
		
	}
	//sauces
	/// <summary>
	/// red,green,yellow,grey
	/// </summary>
	int GetSaucePacketCount(int CurrencyIndex)
	{
		return  0;
	}
	/// <summary>
	/// red,green,yellow,grey
	/// </summary>
	void SetSaucePacketCount(int CurrencyIndex, int Amount)
	{
		//SaucePacketCounts.SetSlot(CurrencyIndex, Amount);
	}

};
USTRUCT(BlueprintType) struct FPlayerAblityInfo
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Toggle to not dissrupt ablities shop first startup
	/// </summary>
	bool Empty = true;
	//Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
	FArrayIntContainer ablityCosts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
	FArrayIntContainer ablityCostMultipliers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
	FArrayIntContainer passiveInts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
	FArrayFloatContainer passiveFloats;
	//bools 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
	FArrayBoolContainer ablityBools;

	//////////////////////
	// costs
	///////////////////
/// <summary>
/// normal,magic
/// </summary>
	int GetAblityCosts(int CurrencyIndex)
	{
		return ablityCosts.GetSlot(CurrencyIndex);
	}
	/// <summary>
	/// 
	/// </summary>
	bool SetAblityCosts(int CurrencyIndex, int Amount)
	{
		return ablityCosts.SetSlot(CurrencyIndex, Amount);
	}
	//////////////////////////
	//bools
	///////////////////////////
/// <summary>
///
/// </summary>
	int GetAblityBools(int CurrencyIndex)
	{
		return   ablityBools.GetSlot(CurrencyIndex);
	}
	/// <summary>
	///
	/// </summary>
	bool SetAblityBools(int CurrencyIndex, bool Amount)
	{
		return ablityBools.SetSlot(CurrencyIndex, Amount);
	}
};
USTRUCT(BlueprintType) struct FPlayerSaveInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Player Info")
		FString playerName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Player Info")
		int  emotionIndex;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Player Info")
		int  skinIndex;
	//Spawn info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int32 mapIndex;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
	//	FVector playerLocation;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
	//	FRotator playerRotation;

	//Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int  HealthCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int  DurationCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int  CapCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int  CapPassive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int  HealthPassive;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int  durlevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int  caplevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		int hplevel;

	//Passive multiplers 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		float HPCostMult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		float durcostmult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		float capcostmult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		float durationpassive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		float playerhealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		float playerMAXhealth;

	//bools 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		bool CanDoubleJump;

	FPlayerSaveInfo& FPlayerSaveInfo::operator =(const FPlayerSaveInfo& other)
	{
		playerName = other.playerName;

		//TO DO Rest 
		return *this;
	}
};




#pragma endregion 
UCLASS()
class DONTSPILLYOURBEANS_API USaveDataSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	/// <summary>
	/// name of the save file
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
		FString saveFileName;

	/// <summary>
	/// contains all player info like location,bean counts ect
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Info")
	FPlayerSaveInfo playerSaveInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Info")
	FPlayerCollectablesInfo playerCollectables;

	/// <summary>
	/// players ablity information
	/// </summary>
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
	//FPlayerAblityInfo playerAblity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving")
	TArray<FString> LevelSaveNames;


	//func
	USaveDataSaveGame();
	UFUNCTION(BlueprintCallable, Category = "Saving")
		bool CheckifSaveExists();

	UFUNCTION(BlueprintCallable, Category = "Saving")
		bool Save();

	UFUNCTION(BlueprintCallable, Category = "Saving")
		void AddLevelSaveName(FString LevelSaveSlotName);

	UFUNCTION(BlueprintCallable, Category = "Saving")
		bool DeleteSave();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving|Passives")
		FArraySlotsContainer items;
		/// <summary>
		/// adds the nescessay vars
		/// </summary>
		/// <returns></returns>

		UFUNCTION(BlueprintCallable, Category = "Saving")
		void SaveAllAblities(TArray<int>&  costs, TArray<int>& durrationsInts, TArray<int>& durrationsFloats, 
			TArray<float>&multiplier, TArray<bool>& bools);


		UFUNCTION(BlueprintCallable, Category = "Saving")
		void SaveAllItems(FArraySlotsContainer& inventory);

		UFUNCTION(BlueprintCallable, Category = "Saving")
		void LoadAllItems(class  AInventoryPlayer * Player);

		UFUNCTION(BlueprintCallable, Category = "Saving")
		void SaveWardrobe(class  ABaseCharacter* Player);

		UFUNCTION(BlueprintCallable, Category = "Loading")
		void LoadWardrobe(class  AInventoryPlayer* Player);
private :
		/// <summary>
		/// used to save a passed in int array 
		/// </summary>
		
};
