// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerStatActor.h"
#include "Interface/AbilityShopWidget.h"


// Sets default values
APlayerStatActor::APlayerStatActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PacketDurationPassive = 0;
	PacketCapacityPassive = 0;
	MaxHealthPassive = 0;
	canDoubleJump = false;

	//this is used to reset the previous application of passives.
	DurationLevel = 0;
	CapacityLevel = 0;
	HPLevel = 0;
	Basehealth = 5.0f;
}

// Called when the game starts or when spawned
void APlayerStatActor::BeginPlay()
{
	Super::BeginPlay();

	//Widget Creation

	//WC_ShopWidget = CreateWidget<UAbilityShopWidget>()
}


void APlayerStatActor::UpdateCosts()
{
	if (IsValid(WC_ShopWidget))
	{
		WC_ShopWidget->CostDur->SetText(FText::AsNumber(DurationCost));
		WC_ShopWidget->CostCap->SetText(FText::AsNumber(CapacityCost));
		WC_ShopWidget->CostHP->SetText(FText::AsNumber(HealthCost));
		
		if (canDoubleJump)
		{
			WC_ShopWidget->CostDJ->SetText(FText::FromString("---"));
			WC_ShopWidget->ButtonDJ->SetIsEnabled(false);
		}
		else 
		{
			WC_ShopWidget->CostDJ->SetText(FText::AsNumber(JumpCost));
		}
	}
}

int APlayerStatActor::IncreaseCost(int cost, float& mult)
{

	cost += mult;
	mult += cost * 0.015f;
	return cost;
}

//Functions used by Upgrade Vender to alter Passives by increment.
void APlayerStatActor::ModifyPacketDuration()
{
	PacketDurationPassive += PacketDurationIncrement;
	OnUpgrade.Broadcast();
	DurationCost = IncreaseCost(DurationCost, DurationCostMultiplier);
	UpdateCosts();
}

void APlayerStatActor::ModifyPacketCapacity()
{
	PacketCapacityPassive += PacketCapacityIncrement;
	OnUpgrade.Broadcast();
	CapacityCost = IncreaseCost(CapacityCost, CapacityCostMultiplier);
	UpdateCosts();
}

void APlayerStatActor::ModifyMaxHealth()
{
	MaxHealthPassive += MaxHealthIncrement;
	OnUpgrade.Broadcast();
	HealthCost = IncreaseCost(HealthCost, HealthCostMultiplier);
	UpdateCosts();
}

void APlayerStatActor::AllowDoubleJump()
{
	canDoubleJump = true;
	OnUpgrade.Broadcast();
	UpdateCosts();
}

void APlayerStatActor::SetupWidget(APlayerController* controller)
{
	WC_ShopWidget = CreateWidget<UAbilityShopWidget>(controller, MyWidget);
	if (IsValid(WC_ShopWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("Made It in"));
		WC_ShopWidget->AddToViewport(2);
		WC_ShopWidget->ExitButton->OnClicked.AddDynamic(this, &APlayerStatActor::HideShop);
		/*WC_ShopWidget->ButtonDur->OnClicked.AddDynamic(this, &APlayerStatActor::ModifyPacketDuration);
		WC_ShopWidget->ButtonCap->OnClicked.AddDynamic(this, &APlayerStatActor::ModifyPacketCapacity);
		WC_ShopWidget->ButtonHP->OnClicked.AddDynamic(this, &APlayerStatActor::ModifyMaxHealth);
		WC_ShopWidget->ButtonDJ->OnClicked.AddDynamic(this, &APlayerStatActor::AllowDoubleJump);*/
		UpdateCosts();
	}

}


//Functions called by the player to apply passives to player stats
float APlayerStatActor::ApplyPacketDurationPassive(float currentDuration) //10 -> 30, 20 -> 40
{
	//if level is 0 and Passive is not 0 then no application as been made yet, add level then add passive.
	if (DurationLevel == 0)
	{
		if (PacketDurationPassive != 0)
			DurationLevel++;

		return (PacketDurationPassive + currentDuration); //if passive is 0 nothing is added and level is not incremented.
	}

	//if passive divided by level is = to increment than it has already been added, return currentStat
	if (PacketDurationPassive / DurationLevel == PacketDurationIncrement)
	{
		return currentDuration;
	}
	else
	{
		//if not an application is needed
		DurationLevel++;
		return (PacketDurationPassive + currentDuration);
	}
}

int APlayerStatActor::ApplyPacketCapacityPassive(float currentCapacity)
{
	//if level is 0 and Passive is not 0 then no application as been made yet, add level then add passive.
	if (CapacityLevel == 0)
	{
		if (PacketCapacityPassive != 0)
			CapacityLevel++;

		return (PacketCapacityPassive + currentCapacity); //if passive is 0 nothing is added and level is not incremented.
	}

	//if passive divided by level is = to increment than it has already been added, return currentStat
	if (PacketCapacityPassive / CapacityLevel == PacketCapacityIncrement)
	{
		return currentCapacity;
	}
	else
	{
		//if not an application is needed
		CapacityLevel++;
		return (PacketCapacityPassive + currentCapacity);
	}
}

int APlayerStatActor::ApplyMaxHealthPassive(float currentMaxHp)
{
	//if level is 0 and Passive is not 0 then no application as been made yet, add level then add passive.
	if (HPLevel == 0)
	{
		if (MaxHealthPassive != 0)
		{
			Basehealth = currentMaxHp;
			HPLevel++;
			EnteredBefore++;
		}


		return (MaxHealthPassive + currentMaxHp); //if passive is 0 nothing is added and level is not incremented.
	}


	//if not an application is needed //25 -> 30; reduce 25 -> 20 add 10 -> 30

	if (currentMaxHp - MaxHealthPassive != Basehealth)
	{
		HPLevel++;
	}

	UE_LOG(LogTemp, Warning, TEXT("level %d , MaxPass %d"), HPLevel, MaxHealthPassive);
	return (MaxHealthPassive + Basehealth);

}

bool APlayerStatActor::ApplyDoubleJumpPassive()
{
	return canDoubleJump;
}

void APlayerStatActor::ShowShop()
{
	if (IsValid(WC_ShopWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget is live"));
		WC_ShopWidget->ShowShop();
	}
}

void APlayerStatActor::HideShop()
{
	if (IsValid(WC_ShopWidget))
	{
		WC_ShopWidget->HidShop();
	}
}


bool APlayerStatActor::ApplyAllPassives(float& PDuration, int& PCapacity, int& MaxHp)
{

	PDuration = ApplyPacketDurationPassive(PDuration);
	PCapacity = ApplyPacketCapacityPassive(PCapacity);
	MaxHp = ApplyMaxHealthPassive(MaxHp);

	return ApplyDoubleJumpPassive();
}


//Mass Getters and Setter for Passive Stats, Intended for Save System.
TArray<float> APlayerStatActor::GetAllCurrentPassives(bool& canJump)
{
	TArray<float> PassoutArry;
	PassoutArry.Add(PacketDurationPassive);
	PassoutArry.Add(PacketCapacityPassive);
	PassoutArry.Add(MaxHealthPassive);
	return PassoutArry;
}

void APlayerStatActor::SetAllCurrentPassives(float PacketDur, int PacketCap, int MaxHp, bool canDouble)
{
	PacketDurationPassive = PacketDur;
	PacketCapacityPassive = PacketCap;
	MaxHealthPassive = MaxHp;
	canDoubleJump = canDouble;
}

