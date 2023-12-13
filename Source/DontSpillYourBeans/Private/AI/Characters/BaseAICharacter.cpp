// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Characters/BaseAICharacter.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"
#include "Pawn/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Drops/ItemProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "Engine/DamageEvents.h"
#include "TimerManager.h"



// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//UE_LOG(LogTemp, Warning, TEXT("AI Character"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseAICharacter::OnCollisionBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseAICharacter::OnCollisionEnd);

	StereoSystem = CreateDefaultSubobject<UAudioComponent>(TEXT("StereoComponent"));
	StereoSystem->SetupAttachment(GetRootComponent());

	TrailZSpawn = 100;
}

// Called when the game starts or when spawned
void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Controller is Valid"));
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();

	if (IsValid(MoveComp))
	{
		MoveComp->MaxWalkSpeed = UnitMovementSpeed;
	}

	AnimGraph = Cast<UEggyAnimEventGraph>(GetMesh()->GetAnimInstance());
	/*if (IsValid(AnimGraph))
		UE_LOG(LogTemp, Warning, TEXT("AnimGraph is VALID"));*/
	IsInRange = false;
	UnitHealth = UnitMaxHealth;
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//test
	ABaseAIController* controller = Cast<ABaseAIController>(GetController());
	//if (!IsValid(controller))
	//	UE_LOG(LogTemp, Error, TEXT("CONTROLLER INVALID"));
}


// Called every frame
void ABaseAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseAICharacter::AttackCall()
{

	//get player character
	if (IsDead || AnimGraph->IsHurt())
		return false;

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	return true;
}

bool ABaseAICharacter::EndAttackCall()
{
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AnimGraph->DeactivateAttack();
	return true;
}

bool ABaseAICharacter::EnemySetup(float Damage, float Health, float Speed, float Pushback)
{
	UnitMaxHealth = Health;
	UnitHealth = UnitMaxHealth;
	AttackDamage = Damage;
	UnitMovementSpeed = Speed;
	Pushbackstrength = Pushback;

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();

	if (IsValid(MoveComp))
	{
		MoveComp->MaxWalkSpeed = UnitMovementSpeed;
	}

	return true;
}

#pragma region Death&Damage

float ABaseAICharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead)
		return 0.f;

	UnitHealth -= Damage;
	//UE_LOG(LogTemp, Warning, TEXT("AI Health: %f"), UnitHealth);

	FDamageEvent dmgEvent = FDamageEvent();
	//calculate pushback
	PushbackVector = (DamageCauser->GetActorLocation() - GetActorLocation()); //a backwards velocity from the player
	//PushbackVector.Normalize();
	PushbackVector *= (Pushbackstrength * 2);
	this->LaunchCharacter(PushbackVector, false, false);
	//UE_LOG(LogTemp, Warning, TEXT("PUSH"));




	if (UnitHealth <= 0.f)
	{
		ABaseAIController* controller = Cast<ABaseAIController>(GetController());
		UBlackboardComponent* Board = controller->GetBlackboardComponent();

		IsDead = true;
		UnitHealth = 0.f;
		OnAIDeath.Broadcast(-1);
		AnimGraph->DeathState(IsDead);
		PlayDeathAudio();
		controller->StopMovement();
		controller->UnPossess();
		controller->Destroy();
		//UE_LOG(LogTemp, Error, TEXT("AI DEAD"));

		float chance = FMath::RandRange(0.01f, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("Chance %f"), chance);
		if (chance < DropChance)
		{
			DropItem();
		}
		KillEnemy();
		return 0.0f;
	}
	else if (UnitHealth >= UnitMaxHealth)
	{
		UnitHealth = UnitMaxHealth;
	}


	//play hurt animation and audio now that we know we aren't dead

	AnimGraph->ActivateHurt();
	PlayHurtAudio();

	return 0.0f;
}

bool ABaseAICharacter::KillEnemy()
{
	FTimerHandle Handler;
	GetWorld()->GetTimerManager().SetTimer(Handler, [&]() {Destroy(); }, 6, false);
	return true;
}

bool ABaseAICharacter::IsAlive()
{

	return !IsDead;
}

bool ABaseAICharacter::DropItem()
{

	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + TrailZSpawn);

	AItemProjectile* SpawnedItem = GetWorld()->SpawnActor<AItemProjectile>(ItemTrail, SpawnLocation, GetActorRotation());

	if (IsValid(SpawnedItem))
	{

		SpawnedItem->ShootItem(GetActorLocation(), GetVelocity());

	}

	return true;

}

#pragma endregion


#pragma region Collision


void ABaseAICharacter::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (IsDead)
		return;

	ABaseCharacter* player = Cast<ABaseCharacter>(OtherActor);

	if (IsValid(player))
	{
		IsInRange = true;
	}

	ABaseAIController* controller = Cast<ABaseAIController>(GetController());

	if (!IsValid(controller))
		return;

	UBlackboardComponent* Board = controller->GetBlackboardComponent();

	if (!IsValid(Board))
		return;

	ACharacter* playerActor = Cast<ACharacter>(Board->GetValueAsObject(FName("Player")));

	if (!IsValid(playerActor))
	{
		//UE_LOG(LogTemp, Error, TEXT("PlayerActor is INVALID"));
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Player isValid"));

	if (IsInRange)
	{
		//play animation
		//AnimGraph->ActivateAttack();
		//reduce health
		FDamageEvent dmgEvent = FDamageEvent();
		if (PlaySoundOnHit)
			PlayAttackAudio();
		playerActor->TakeDamage(AttackDamage, dmgEvent, this->GetInstigatorController(), this);
		//calculate pushback
		PushbackVector = (playerActor->GetActorLocation() - GetActorLocation()); //a backwards velocity from the player
		//PushbackVector.Normalize();
		PushbackVector *= Pushbackstrength;
		playerActor->LaunchCharacter(PushbackVector, false, false);
	}


	//provide pushback vector to player;
}

void ABaseAICharacter::OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABaseCharacter* player = Cast<ABaseCharacter>(OtherActor);

	if (IsValid(player))
	{
		IsInRange = false;
	}

}

#pragma endregion


#pragma region Audio


void ABaseAICharacter::PlayAttackAudio()
{
	if (AttackAudios.IsEmpty())
		return;

	int indx = FMath::RandRange(0, AttackAudios.Num() - 1);
	if (!StereoSystem->IsPlaying())
	{
		StereoSystem->Sound = AttackAudios[indx];
		StereoSystem->Play();
	}
}

void ABaseAICharacter::PlayHurtAudio()
{
	UE_LOG(LogTemp, Warning, TEXT(" in hurt"));
	if (HurtAudios.IsEmpty())
		return;


	int indx = FMath::RandRange(0, HurtAudios.Num() - 1);
	//UE_LOG(LogTemp, Warning, TEXT(" in hurt indx: %d"), indx);
	if (!StereoSystem->IsPlaying())
	{
		//UE_LOG(LogTemp, Warning, TEXT(" in hurt play"));
		StereoSystem->Stop();
		StereoSystem->Sound = HurtAudios[indx];
		StereoSystem->Play();
	}



}

void ABaseAICharacter::PlayDeathAudio()
{

	if (!IsValid(DeathAudio))
		return;

	if (StereoSystem->Sound != DeathAudio)
	{
		StereoSystem->Stop();
		StereoSystem->Sound = DeathAudio;
		StereoSystem->Play();
	}

}

void ABaseAICharacter::PlayCallAudio()
{

	if (!IsValid(CallAudio))
		return;

	if (!StereoSystem->IsPlaying())
	{
		StereoSystem->Sound = CallAudio;
		StereoSystem->Play();
	}

}

void ABaseAICharacter::PlayMovementAudio()
{
	if (MovementAudios.IsEmpty())
		return;


	int indx = FMath::RandRange(0, MovementAudios.Num() - 1);

	if (!StereoSystem->IsPlaying())
	{
		StereoSystem->Sound = MovementAudios[indx];
		StereoSystem->Play();
	}

}


#pragma endregion


