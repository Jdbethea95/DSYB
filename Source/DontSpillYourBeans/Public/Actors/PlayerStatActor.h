// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStatActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShopDelegate);

UCLASS()
class DONTSPILLYOURBEANS_API APlayerStatActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStatActor();

	FShopDelegate OnUpgrade;


	//Increments that will determine how much each stat increases when upgraded
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passives | Increment")
		float PacketDurationIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passives | Increment")
		int PacketCapacityIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passives | Increment")
		int MaxHealthIncrement;

	//item Costs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop | Initial Prices")
		int HealthCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop | Initial Prices")
		int JumpCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop | Initial Prices")
		int DurationCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop | Initial Prices")
		int CapacityCost;

	//Cost Increments
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop | Increase")
		float HealthCostMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop | Increase")
		float JumpCostMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop | Increase")
		float DurationCostMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop | Increase")
		float CapacityCostMultiplier;

		//MOVED THESE TO PUBLIC 

	//Values that will increase playerstats upon load.
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Passives")
		float PacketDurationPassive;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Passives")
		int PacketCapacityPassive;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Passives")
		int MaxHealthPassive;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Passives")
		bool canDoubleJump;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Passives | Levels")
		int DurationLevel;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Passives | Levels")
		int CapacityLevel;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Passives | Levels")
		int HPLevel;


		void UpdateCosts();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	int IncreaseCost(int cost, float& mult);
	//Widget Protected Items
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UAbilityShopWidget> MyWidget;

	int EnteredBefore = 0;

public:	

	//Widget Public Items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UAbilityShopWidget* WC_ShopWidget;

	//Functions That are called by the Upgrade Vender.
	UFUNCTION()
	void ModifyPacketDuration();
	UFUNCTION()
	void ModifyPacketCapacity();
	UFUNCTION()
	void ModifyMaxHealth();
	UFUNCTION()
	void AllowDoubleJump();


	void SetupWidget(APlayerController* controller);

	//Function that are called by the player to apply passives
	float ApplyPacketDurationPassive(float currentDuration);
	int ApplyPacketCapacityPassive(float currentCapacity);
	int ApplyMaxHealthPassive(float currentMaxHp);
	bool ApplyDoubleJumpPassive();


	void ShowShop();
	UFUNCTION()
	void HideShop();


	/// <summary>
	/// Takes in current stats as reference to modify.
	/// Returns the bool for canDoubleJump.
	/// </summary>
	/// <param name="PDuration"></param>
	/// <param name="PCapacity"></param>
	/// <param name="MaxHp"></param>
	/// <returns></returns>
	bool ApplyAllPassives(float& PDuration, int& PCapacity, int& MaxHp);

	/// <summary>
	/// Returns Array of {PacketCap, PacketDur, MaxHp}
	/// and takes a bool as reference to be assigned from
	/// canDoubleJump.
	/// </summary>
	/// <param name="canJump">: Used to get local bool Variable</param>
	/// <returns></returns>
	TArray<float> GetAllCurrentPassives(bool& canJump);

	void SetAllCurrentPassives(float PacketDur, int PacketCap, int MaxHp, bool canDouble);

private:
	int Basehealth;
	float BaseDuration;
	int BaseCapacity;
};
