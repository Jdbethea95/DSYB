// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Materials/MaterialInstance.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/AbilityShopWidget.h"
#include "TimerManager.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArm->TargetArmLength = 420;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);


	WeaponChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponComponent"));
	WeaponChildComponent->SetupAttachment(GetMesh(), FName("SwordPlacement"));

	SwordColldierComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SwordCollider"));
	SwordColldierComponent->SetupAttachment(WeaponChildComponent);

	IsDead = false;
	SkinIndex = 0;
	EmoIndex = 0;
	//Passive stats Component

	PassiveStatComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("PassiveStatComponent"));
	PassiveStatComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Setting Up New Input System
	APlayerController* Inputcontroller = Cast<APlayerController>(GetController());

	if (IsValid(Inputcontroller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Inputcontroller->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 99);

		}
	}


	//setting Up Player Weapon
	WeaponChildComponent->SetChildActorClass(WeaponRef, SwordWeapon);

	if (IsValid(WeaponChildComponent->GetChildActor()))
	{
		SwordWeapon = Cast<ASwordActor>(WeaponChildComponent->GetChildActor());
		if (IsValid(SwordWeapon))
		{
			SwordWeapon->SetSwordOwner(this);
			SwordColldierComponent->OnComponentBeginOverlap.AddDynamic(SwordWeapon, &ASwordActor::OnCollisionBegin);

			SwordWeapon->SetSwordDamage(playerStats[2]);
			SwordColldierComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	//Setting up Animation
	Animations = Cast<UPlayerAnimGraph>(GetMesh()->GetAnimInstance());
	if (IsValid(Animations))
	{
		OnDeath.AddDynamic(Animations, &UPlayerAnimGraph::PlayDeath);
	}

	//Seting up Passive Stat Component
	PassiveStatComponent->SetChildActorClass(PassiveStatRef, PassiveStatActor);

	if (IsValid(PassiveStatComponent->GetChildActor()))
	{
		PassiveStatActor = Cast<APlayerStatActor>(PassiveStatComponent->GetChildActor());
		if (IsValid(PassiveStatActor))
		{
			//Do Passive Setups if load is needed.
			APlayerController* controller = Cast<APlayerController>(GetController());
			if (IsValid(controller))
			{
				//The widget needs an owning player controller so the setup is done after with a 
					//function called in baseCharacter to provide the owner.
				PassiveStatActor->SetupWidget(controller);
				SetUpOnclicks();
			}
			PassiveStatActor->OnUpgrade.AddDynamic(this, &ABaseCharacter::OnModifyStats);
		}
	}

	playerStats[3] = GetCharacterMovement()->JumpZVelocity;
	playerStats[0] = 0;
	playerStats[1] = GetCharacterMovement()->MaxWalkSpeed;
	CanDoubleJump = false;
	SpawnLocation = GetActorLocation();

	UE_LOG(LogTemp, Error, TEXT("MaxHealth: %f"), PlayerMaxHealth);
}

bool ABaseCharacter::ApplySkinAndEmo(int Skindex, int EmoDex)
{
	if (Skindex >= PlayerSkins.Num() || EmoDex >= PlayerEmos.Num())
		return false;

	SkinIndex = Skindex;
	EmoIndex = EmoDex;
	GetMesh()->SetMaterial(0, PlayerSkins[SkinIndex]);
	GetMesh()->SetMaterial(1, PlayerEmos[EmoIndex]);
	return true;
}

bool ABaseCharacter::ApplySkin(int Skindex)
{
	if (Skindex >= PlayerSkins.Num())
		return false;


	SkinIndex = Skindex;
	GetMesh()->SetMaterial(0, PlayerSkins[SkinIndex]);
	return true;
}

bool ABaseCharacter::ApplyEmo(int Emodex)
{
	if (Emodex >= PlayerEmos.Num())
		return false;


	EmoIndex = Emodex;
	GetMesh()->SetMaterial(1, PlayerEmos[EmoIndex]);
	return true;
}

bool ABaseCharacter::ModifyHealth(float amount)
{
	PlayerHealth += amount;

	if (PlayerHealth >= PlayerMaxHealth)
	{
		PlayerHealth = PlayerMaxHealth;
	}
	return true;
}

#pragma region Input-Functions

void ABaseCharacter::MoveForward(float AxisValue)
{
	if (IsDead)
		return;
	FRotator MakeRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	AddMovementInput(MakeRotation.Vector(), (AxisValue * playerStats[1]));
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	if (IsDead)
		return;
	FVector RightFace = GetActorRightVector();
	AddMovementInput(RightFace, (AxisValue * playerStats[1]));
}

void ABaseCharacter::EnhancedMove(const FInputActionValue& Value)
{
	//Grab Information from InputAction Value
	FVector2D movementVector = Value.Get<FVector2D>();

	//Handle Right Movement
	FVector RightFace = GetActorRightVector();
	AddMovementInput(RightFace, movementVector.X);

	//Handle Forward Movement
	FRotator MakeRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	AddMovementInput(MakeRotation.Vector(), movementVector.Y);
}

void ABaseCharacter::EnhancedLook(const FInputActionValue& Value)
{
	//Get value out of InputAction
	FVector2D lookVector = Value.Get<FVector2D>();

	AddControllerYawInput(lookVector.X);
	AddControllerPitchInput(lookVector.Y);

}

void ABaseCharacter::PlayerJump()
{
	if (IsDead)
		return;
	Animations->PlayJump();
	Jump();
}

void ABaseCharacter::Attack()
{
	if (IsDead)
		return;
	Animations->PlayAttack();
}

void ABaseCharacter::Interact()
{
	OnInteract.Broadcast();
}

void ABaseCharacter::TimerBegin()
{
	GetWorld()->GetTimerManager().SetTimer(ComboTimer,
		[&]()
		{
			comboCount++;
			Attack();
		},
		1.f, false);
}

void ABaseCharacter::TimerEnd()
{
	if (comboCount >= comboAttacks.Num())
	{
		ResetCombo();
	}
}

void ABaseCharacter::ResetCombo()
{
	GetWorld()->GetTimerManager().ClearTimer(ComboTimer);
	comboCount = 0;
}

#pragma endregion

void ABaseCharacter::OnModifyStats()
{
	if (IsValid(PassiveStatActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("In Health: %f"), PlayerMaxHealth);
		PlayerMaxHealth = PassiveStatActor->ApplyMaxHealthPassive(PlayerMaxHealth);
		UE_LOG(LogTemp, Warning, TEXT("Out Health: %f"), PlayerMaxHealth);
		ModifyHealth(PlayerMaxHealth); //Called simply to have inventory player update HP Bar
		CanDoubleJump = PassiveStatActor->ApplyDoubleJumpPassive();
		if (CanDoubleJump)
			JumpMaxCount = 2;
	}
}

void ABaseCharacter::TabLeft(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("tab left: %d"), Value.Get<bool>());
	OnTabLeft.Broadcast();
}

void ABaseCharacter::TabRight(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("tab left: %d"), Value.Get<bool>());
	OnTabRight.Broadcast();
}
//Debug menu 
#pragma region Menu-Functions

void ABaseCharacter::ToggleDebugMenu(bool isPaused)
{
	if (isPaused)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Debug menu : True"));
		ShowDebugMenu();
		ActivateUIContext();
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Debug menu : false"));
		RemoveDebugMenu();
		DeActivateUIContext();
	}
}
void ABaseCharacter::DebugMenu(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Debug menu button Pressed"));
	ToggleDebugMenu(TogglePause());
}
void ABaseCharacter::ActivateUIContext()
{
	//Setting Up New Input System
	APlayerController* Inputcontroller = Cast<APlayerController>(GetController());

	if (IsValid(Inputcontroller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Inputcontroller->GetLocalPlayer()))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Changing maping : UI"));
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(UIMappingContext, 99);
			Inputcontroller->SetShowMouseCursor(true);
			//Set up input mode
		//input to UI only
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			Inputcontroller->SetInputMode(InputMode);
		}
	}


}
void ABaseCharacter::DeActivateUIContext()
{
	//Setting Up New Input System
	APlayerController* Inputcontroller = Cast<APlayerController>(GetController());

	if (IsValid(Inputcontroller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Inputcontroller->GetLocalPlayer()))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Changing maping : Default"));
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 99);
			Inputcontroller->SetShowMouseCursor(false);
			//input to UI only
			FInputModeGameOnly  InputMode;
			//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			Inputcontroller->SetInputMode(InputMode);
		}
	}

}
void ABaseCharacter::Pause(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Pause Pressed"));
	TogglePauseMenu(TogglePause());
}
bool  ABaseCharacter::TogglePause()
{
	APlayerController* Inputcontroller = Cast<APlayerController>(GetController());
	if (Inputcontroller != nullptr)
	{
		bool isPaused = Inputcontroller->IsPaused();
		if (isPaused)
		{
			// paused so unpause
			//UE_LOG(LogTemp, Warning, TEXT("Pause : false"));
			Inputcontroller->SetPause(false);
			return false;
		}
		else
		{
			// !paused so  pause 
			//UE_LOG(LogTemp, Warning, TEXT("Pause : true"));
			Inputcontroller->SetPause(true);

			return true;
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Inputcontroller null"));
		return false;
	}

}
void ABaseCharacter::TogglePauseMenu(bool isPaused)
{
	if (isPaused)
	{
		ShowPauseMenu();
		ActivateUIContext();
	}
	else
	{
		RemovePauseMenu();
		DeActivateUIContext();
	}
}
void ABaseCharacter::ShowPauseMenu()
{
	APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller != nullptr)
	{
		if (PauseMenuRef == nullptr)
		{

			//make menu
			UUserWidget* ScreenWidget = CreateWidget<UUserWidget>(controller, PauseMenuClass);
			//check if worked
			if (ScreenWidget != nullptr)
			{

				PauseMenuRef = ScreenWidget;
			}
		}

		if (PauseMenuRef != nullptr)
		{

			//add UI to view
			PauseMenuRef->AddToViewport();


		}
	}



}
void ABaseCharacter::RemovePauseMenu()
{
	if (PauseMenuRef != nullptr)
	{
		PauseMenuRef->RemoveFromParent();
	}
}
void ABaseCharacter::ShowDebugMenu()
{

	APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller != nullptr)
	{
		if (DebugMenuRef == nullptr)
		{

			//make menu
			UUserWidget* ScreenWidget = CreateWidget<UUserWidget>(controller, DebugMenuClass);
			//check if worked
			if (ScreenWidget != nullptr)
			{

				DebugMenuRef = ScreenWidget;
			}
		}

		if (DebugMenuRef != nullptr)
		{

			//add UI to view
			DebugMenuRef->AddToViewport();


		}
	}


}
void ABaseCharacter::RemoveDebugMenu()
{
	if (DebugMenuRef != nullptr)
	{
		DebugMenuRef->RemoveFromParent();
	}


}
#pragma endregion

#pragma region Shop-Functions

void ABaseCharacter::PurchaseDuration()
{
	PassiveStatActor->ModifyPacketDuration();
}


void ABaseCharacter::PurchaseCapacity()
{
	PassiveStatActor->ModifyPacketCapacity();
}

void ABaseCharacter::PurchaseHealth()
{
	PassiveStatActor->ModifyMaxHealth();
}

void ABaseCharacter::PurchaseDoubleJump()
{
	PassiveStatActor->AllowDoubleJump();
}

void ABaseCharacter::SetUpOnclicks()
{
	PassiveStatActor->WC_ShopWidget->ButtonDur->OnClicked.AddDynamic(this, &ABaseCharacter::PurchaseDuration);
	PassiveStatActor->WC_ShopWidget->ButtonCap->OnClicked.AddDynamic(this, &ABaseCharacter::PurchaseCapacity);
	PassiveStatActor->WC_ShopWidget->ButtonHP->OnClicked.AddDynamic(this, &ABaseCharacter::PurchaseHealth);
	PassiveStatActor->WC_ShopWidget->ButtonDJ->OnClicked.AddDynamic(this, &ABaseCharacter::PurchaseDoubleJump);
}

#pragma endregion


float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsPaused || IsDead)
		return 0.f;

	PlayerHealth -= Damage;


	//play hurt sound

	if (PlayerHealth <= 0.f)
	{
		PlayerHealth = 0.f;
		IsDead = true;
		OnDeath.Broadcast();
		//TogglePause();
	}
	else if (PlayerHealth >= PlayerMaxHealth)
	{
		PlayerHealth = PlayerMaxHealth;
	}
	//play hurt animation
	Animations->PlayHurt();

	return 0.0f;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::StartAttack()
{
	SwordColldierComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SwordWeapon->SwingSword();
}

void ABaseCharacter::EndAttack()
{
	SwordColldierComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SwordWeapon->StopSword();
}

void ABaseCharacter::ActivatePacket(int Index, int Duration)
{
	//test, Both Index and Duration is becoming 0 when passed from inventory player. Weird

	if (Index >= effectValues.Num() || Index < 0)
	{
		//UE_LOG(LogTemp, Error, TEXT("Packet Out of Bounds: %d"), Index);
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("PacketStart: Dur[ %d ] | indx [ %d ]"), Duration, Index);
	playerStats[Index] += effectValues[Index];
	MainIndex = Index;
	UpdateStats();
	GetWorld()->GetTimerManager().SetTimer(Timer, [&]() {DeactivatePacket(MainIndex); }, Duration, false);
}

void ABaseCharacter::DeactivatePacket(int Index)
{
	if (Index >= effectValues.Num() || Index < 0)
	{
		//UE_LOG(LogTemp, Error, TEXT("Packet Out of Bounds: %d"), Index);
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("PacketStart: indx [ %d ]"), Index);
	playerStats[Index] -= effectValues[Index];
	UpdateStats();
}

void ABaseCharacter::UpdateStats()
{
	SwordWeapon->SetSwordDamage(playerStats[2]);
	GetCharacterMovement()->JumpZVelocity = playerStats[3];
	GetCharacterMovement()->MaxWalkSpeed = playerStats[1];
	ModifyHealth(playerStats[0]);
}

void ABaseCharacter::PushVector(float pushStrength, FVector SourceActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Str: %d"), 5);
	FVector pushbackVector;
	pushbackVector = (GetActorLocation() - SourceActor);
	pushbackVector *= pushStrength;
	pushbackVector.Z = 600;
	PlayerJump();
	LaunchCharacter(pushbackVector, false, false);

}


// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	inputComp = PlayerInputComponent;

	//Enhanced Input Component
	UEnhancedInputComponent* enhancedComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(enhancedComponent))
	{
		enhancedComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::EnhancedMove);
		enhancedComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::EnhancedLook);
		enhancedComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ABaseCharacter::PlayerJump);
		enhancedComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ABaseCharacter::StopJumping);
		enhancedComponent->BindAction(AttackInputAction, ETriggerEvent::Started, this, &ABaseCharacter::Attack);
		enhancedComponent->BindAction(InteractInputAction, ETriggerEvent::Started, this, &ABaseCharacter::Interact);
		//UI input
		enhancedComponent->BindAction(DebugInputAction, ETriggerEvent::Started, this, &ABaseCharacter::DebugMenu);
		enhancedComponent->BindAction(PauseInputAction, ETriggerEvent::Started, this, &ABaseCharacter::Pause);
		enhancedComponent->BindAction(TabLeftInputAction, ETriggerEvent::Started, this, &ABaseCharacter::TabLeft);
		enhancedComponent->BindAction(TabRightInputAction, ETriggerEvent::Started, this, &ABaseCharacter::TabRight);
	}

}

void ABaseCharacter::TogglePlayerPauseState()
{
	SetPlayerPauseState(!IsPaused);
}

void ABaseCharacter::SetPlayerPauseState(bool condition)
{
	IsPaused = condition;

	if (IsPaused)
	{
		inputComp->Deactivate();
	}
	else
	{
		inputComp->Activate();
	}
}

void ABaseCharacter::PlayerReset()
{
	//UE_LOG(LogTemp, Error, TEXT("RESET CALLED"));
	//TogglePause();
	PlayerHealth = PlayerMaxHealth;
	IsDead = false;
	Animations->isDeath = IsDead;
	IsPaused = false;
	if (MainIndex >= 0 && MainIndex <= 3)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(Timer))
		{
			GetWorld()->GetTimerManager().ClearTimer(Timer); //Inventory player will need to stop its own timers.
			DeactivatePacket(MainIndex);
		}
	}

	SetActorLocation(SpawnLocation);
}

void ABaseCharacter::LoadShopCosts(int DurationCost, int CapacityCost, int healthCost, int JumpCost)
{
	PassiveStatActor->CapacityCost = CapacityCost;
	PassiveStatActor->DurationCost = DurationCost;
	PassiveStatActor->HealthCost = healthCost;
	PassiveStatActor->JumpCost = JumpCost;

}

//void ABaseCharacter::OnAttackAction(const FInputActionValue& Attack)
//{
//	if (!isAttacking)
//	{
//		IncrementCombo();
//		isAttacking = true;
//	}
//}
//
//void ABaseCharacter::IncrementCombo()
//{
//	ComboCount++;
//	if (ComboCount >= ComboAttacks.Num())
//	{
//		ResetCombo();
//	}
//	GetWorld()->GetTimerManager().SetTimer(ComboTimer, 
//		[&]() 
//		{
//			Attack();
//		}, 
//		1.f, false);
//}
//
//void ABaseCharacter::ResetCombo()
//{
//	ComboCount = 0;
//	if (GetWorld()->GetTimerManager().IsTimerActive(ComboTimer))
//	{
//		GetWorld()->GetTimerManager().ClearTimer(ComboTimer);
//	}
//}




