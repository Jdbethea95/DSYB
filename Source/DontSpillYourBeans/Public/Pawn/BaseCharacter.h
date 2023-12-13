// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actors/SwordActor.h"
#include "Components/ChildActorComponent.h"
#include "Actors/PlayerStatActor.h"
#include "Utility/PlayerAnimGraph.h"
#include "InputAction.h"
#include "BaseCharacter.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

UCLASS()
class DONTSPILLYOURBEANS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		FOnPlayerDeath OnDeath;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		FOnPlayerDeath OnInteract;

		UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		FOnPlayerDeath OnTabRight;

		UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		FOnPlayerDeath OnTabLeft;
		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Skin")
			int SkinIndex;
		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Skin")
			int EmoIndex;

#pragma region WeaponComponents

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UChildActorComponent* WeaponChildComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Reference")
		TSubclassOf<class ASwordActor> WeaponRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ASwordActor* SwordWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float comboCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ComboAnim")
	TArray<UAnimMontage*> comboAttacks;
	

#pragma endregion


#pragma region PlayerStatComponents

	//passive ability components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UChildActorComponent* PassiveStatComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Reference")
		TSubclassOf<class APlayerStatActor> PassiveStatRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		APlayerStatActor* PassiveStatActor;

#pragma endregion


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UPlayerAnimGraph* Animations;
	void TimerBegin();
	void TimerEnd();
	void ResetCombo();

	/// <summary>
	/// Increments health by adding amount.
	/// Use negative to reduce health.
	/// </summary>
	/// <param name="amount">: The amount the health will be incremented by</param>
	/// <returns></returns>
	virtual bool ModifyHealth(float amount);
	virtual bool ApplySkinAndEmo(int Skindex, int EmoDex);
	virtual bool ApplySkin(int Skindex);
	virtual bool ApplyEmo(int Emodex);

	//MOVED HEALTH 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float PlayerHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float PlayerMaxHealth;

	//Pausing 
	UFUNCTION(BlueprintCallable)
		bool TogglePause();
private:

	UInputComponent* inputComp;
	FVector SpawnLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
		class APlayerController* PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float JumpForce = 981.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* SwordColldierComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
		TArray<class UMaterialInstance*> PlayerSkins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
		TArray<class UMaterialInstance*> PlayerEmos;
#pragma endregion


#pragma region Input Objects

	//Enhanced Input system Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Contexts")
		UInputMappingContext* DefaultMappingContext;


		//Enhanced Input system Objects
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Contexts")
		UInputMappingContext* UIMappingContext;

	//InputActions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
		UInputAction* MoveInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
		UInputAction* LookInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
		UInputAction* JumpInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
		UInputAction* AttackInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
		UInputAction* InteractInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
		UInputAction* PauseInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
		UInputAction* InventoryInputAction;
#pragma region UI



		// UI

	//InputActions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
	UInputAction* TabRightInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
	UInputAction* TabLeftInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input | Actions")
	UInputAction* DebugInputAction;

	void TabLeft(const FInputActionValue& Value);
	void TabRight(const FInputActionValue& Value);
	void Pause(const FInputActionValue& Value);
	void DebugMenu(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void ActivateUIContext();
	UFUNCTION(BlueprintCallable)
	void DeActivateUIContext();



	//Debug menu 
	UFUNCTION(BlueprintCallable)
	void ToggleDebugMenu(bool isPaused);

	UFUNCTION(BlueprintCallable)
	void ShowDebugMenu();
	UFUNCTION(BlueprintCallable)
	void RemoveDebugMenu();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Pause")
	class UUserWidget* DebugMenuRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Pause")
	TSubclassOf<class UUserWidget> DebugMenuClass;

	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu(bool isPaused);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Pause")
	class UUserWidget* PauseMenuRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Pause")
	TSubclassOf<class UUserWidget> PauseMenuClass;

	UFUNCTION(BlueprintCallable)
	void ShowPauseMenu();
	UFUNCTION(BlueprintCallable)
	void RemovePauseMenu();

#pragma endregion
#pragma endregion


#pragma region PlayerStatActor

	//PlayerStatActor Functions For Widget

	UFUNCTION()
		/// <summary>
		///  When Inherited, Call Super Only if Cost was Met.
		/// When Cost is met, Call super, then On PassiveStatActor
		/// Call ApplyPacketDuration, and ApplyPacketCapacity
		/// </summary>
		virtual void OnModifyStats();

	void SetUpOnclicks();
	//Wrapper Functions created so Inventory player can add in cost check.
	UFUNCTION()
		virtual void PurchaseDuration();
	UFUNCTION()
		virtual void PurchaseCapacity();
	UFUNCTION()
		virtual void PurchaseHealth();
	UFUNCTION()
		virtual void PurchaseDoubleJump();
#pragma endregion


#pragma region InputFunctions

	//Old Movement Functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//Enhanced Movement functions
	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);

	void PlayerJump();
	void Attack();
	void Interact();
	

#pragma endregion


	/// <summary>
	/// Overrided Actor Function that Applies Damage to BaseCharacter
	/// </summary>
	/// <param name="Damage"> - the damage to be applied</param>
	/// <param name="DamageEvent"> - Not used</param>
	/// <param name="EventInstigator"> - Damage Source's Event Instigator</param>
	/// <param name="DamageCauser"> - refernce to the Actor damage source</param>
	/// <returns></returns>
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;



	bool inAir;
	bool IsPaused;
	bool IsDead;
	bool CanDoubleJump;
	int MainIndex;
	//bool isAttacking;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartAttack();
	void EndAttack();


	//Combo Functionality
	//void OnAttackAction(const FInputActionValue& Value);
	//void IncrementCombo();
	//void ResetCombo();
	FTimerHandle ComboTimer;

	void ActivatePacket(int Index, int Duration);
	void DeactivatePacket(int Index);

	void UpdateStats();

	void PushVector(float pushStrength, FVector SourceActor);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
		virtual void SetPlayerPauseState(bool condition);
	UFUNCTION(BlueprintCallable)
		virtual void TogglePlayerPauseState();
	UFUNCTION(BlueprintCallable)
		virtual void PlayerReset();

	UFUNCTION()
		void LoadShopCosts(int DurationCost, int CapacityCost, int healthCost, int JumpCost);

	//array and timer for Sauce Packet call
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		TArray<int> playerStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		TArray<int> effectValues;
	FTimerHandle Timer;

};
