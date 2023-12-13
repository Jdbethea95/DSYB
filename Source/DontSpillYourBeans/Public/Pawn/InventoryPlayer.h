// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/BaseCharacter.h"
#include "Utility/FunctionMap.h"
#include "Actors/ActorComponents/PlayerQuestComponent.h"
#include "InventoryPlayer.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum ReturnTypes
{
	RT_NULLPTR UMETA(DisplayName = "Nullptr"),
	RT_TRUE UMETA(DisplayName = "TRUE"),
	RT_FALSE UMETA(DisplayName = "FALSE"),
	RT_COMPLETE UMETA(DisplayName = "COMPLETE")
};

UCLASS()
class DONTSPILLYOURBEANS_API AInventoryPlayer : public ABaseCharacter
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	//For Saving 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class 	UMyGameInstance* GamesInstance;
	//Widget Related Stuff
	UPROPERTY(VisibleAnywhere)
		UUserWidget* UserWidget;

	//ADD TO CODING STANDARDS
	//Pre-Fix WC = Widget Component
	//Widget Component is leaf node of a Widget Blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBeanCountUserWidget* WC_BeanCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USaucePacketRadialMenuWidget* WC_RadialMenu;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UHealthEffectWidget* WC_HealthEffect;

	APlayerController* PlayerController;

public:
	
	AInventoryPlayer();

	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UPlayerQuestComponent* QuestComponent;

	//Widgets
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UPlayerPromptWidget* WC_PlayerPrompt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UQuestLogWidget* WC_QuestLog;

	//Bean Counts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beans Counts")
		int currBeanCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beans Counts")
		int currMagicBeanCount;
	//Packet Counts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Packet Counts")
		int currRedPacketCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Packet Counts")
		int currGreenPacketCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Packet Counts")
		int currYellowPacketCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Packet Counts")
		int currGreyPacketCount;


	// When information is needed inside of a blueprint like a mesh or image
	// think of TSubClassOf, assign this to the parent class of the desired blueprint
	// and then in the owning blueprint class of THIS script set the Tsub to
	// the desired class that is inherited by the blueprint you wish to use.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|Class")
		TSubclassOf<class UBeanCountUserWidget> BeanCountBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|Class")
		TSubclassOf<class USaucePacketRadialMenuWidget> RadialMenuBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|Class")
		TSubclassOf<class UHealthEffectWidget> HealthEffectBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|Class")
		TSubclassOf<class UPlayerPromptWidget> PlayerPromptBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|Class")
		TSubclassOf<class UQuestLogWidget> QuestLogBase;

	// Used for inventory related input (Example: "Tab" = toggle hud, L-Click = Use, etc...)
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input Functions and Variables
	void ToggleBeanCount();
	void ToggleRadialMenu();
	void ToggleQuestLogMenu();

	UFUNCTION()
		void ActivateGreenPacket();
	UFUNCTION()
		void ActivateYellowPacket();
	UFUNCTION()
		void ActivateRedPacket();
	UFUNCTION()
		void ActivateGreyPacket();

	// Decides whether an item can be added to the radial wheel.
	UFUNCTION(BlueprintCallable)
	bool AddItem(FName itemID, int count = 1);

	//Adds a normal or magic bean
	bool AddBeanItem(int count = 1);

	//Adds magic bean to players inventory
	bool AddMagicBeanItem(int count = 1);

	//Adds key item to player inventory
	bool AddKeyItem(int count = 1);

	//Adds consumable item to players inventory
	bool AddConsumableItem(int count = 1);

	//Packet Adds
	bool AddRedPacketItem(int count = 1);
	bool AddGreenPacketItem(int count = 1);
	bool AddYellowPacketItem(int count = 1);
	bool AddGreyPacketItem(int count = 1);
	//Packet Removes
	bool RemoveRedPacketItem();
	bool RemoveGreenPacketItem();
	bool RemoveYellowPacketItem();
	bool RemoveGreyPacketItem();

#pragma region BaseCharacter Overrides

	//Overridden BaseCharacter functions
	//Wrapper Functions created so Inventory player can add in cost check.
	virtual void SetPlayerPauseState(bool condition)override;

	virtual void TogglePlayerPauseState()override;

	virtual void PlayerReset() override;

	virtual bool ModifyHealth(float amount) override;

	virtual void OnModifyStats();

	virtual void PurchaseDuration();

	virtual void PurchaseCapacity();

	virtual void PurchaseHealth();

	virtual void PurchaseDoubleJump();

#pragma endregion

	void HandleHealthBar();

	/// <summary>
	/// Overrided Actor Function that Applies Damage to BaseCharacter
	/// </summary>
	/// <param name="Damage"> - the damage to be applied</param>
	/// <param name="DamageEvent"> - Not used</param>
	/// <param name="EventInstigator"> - Damage Source's Event Instigator</param>
	/// <param name="DamageCauser"> - refernce to the Actor damage source</param>
	/// <returns> Float - Percent value of players current health</returns>
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
#pragma region Saving Related
	virtual void SavePlayerData();
	virtual void LoadPlayerData();

#pragma endregion

protected:

	int PacketCapacity;

	//How to get item factory from the blueprint.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|Factory")
		TSubclassOf<class UItemFactoryObject> subItemFactory;

	//Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
		UInputAction* QuestLogInputAction;
private:

	// Used for toggling to viewport
	bool isBeanCountShowing;
	bool isRadialMenuShowing;
	bool isQuestLogMenuShowing;

	FLinearColor GreenTint = FLinearColor(0.0f, 1.0f, 0.0f, 2.0f);
	FLinearColor YellowTint = FLinearColor(1.0f, 1.0f, 1.0f, 2.0f);
	FLinearColor RedTint = FLinearColor(1.0f, 0.0f, 0.0f, 2.0f);
	FLinearColor OrangeTint = FLinearColor(1.0f, 0.647f, 0.0f, 2.0f);
	FLinearColor GreyTint = FLinearColor(0.5f, 0.5f, 0.5f, 2.0f);

	UItemFactoryObject* ItemFactory;

	FunctionMap AddFunctionsMap;

	void InitializeFunctionPointers();
};
