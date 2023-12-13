// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Characters/ChargeAIBoss.h"
#include "Pawn/BaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "Engine/EngineTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AChargeAIBoss::AChargeAIBoss()
{
	IsCharging = false;
	HomeLocation = GetActorLocation();
}


void AChargeAIBoss::BeginPlay()
{
	Super::BeginPlay();
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (IsValid(MoveComp))
	{
		RunSpeed = MoveComp->MaxWalkSpeed * 2;
		UnitAccel = MoveComp->MaxAcceleration;
	}
}


bool AChargeAIBoss::AttackCall()
{
	if (IsDead || IsCharging)
		return false;

	AnimGraph->ActivateAttack();
	IsCharging = true;
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();

	int indx = FMath::RandRange(0, EnemySounds.Num() - 1);
	PlayEnemyCall(EnemySounds[indx]);
	if (IsValid(MoveComp))
	{
		MoveComp->MaxWalkSpeed = RunSpeed * ChargeSpeedMultiplier;
		MoveComp->MaxAcceleration = UnitAccel * AccelMultiplier;
	}
	else
	{
		return false;
	}

	return true;
}

bool AChargeAIBoss::EndAttackCall()
{
	if (IsDead || !IsCharging)
		return false;
	AnimGraph->DeactivateAttack();
	IsCharging = false;
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();

	if (IsValid(MoveComp))
	{
		MoveComp->MaxWalkSpeed = UnitMovementSpeed;
		MoveComp->MaxAcceleration = UnitAccel;
	}
	else
	{
		return false;
	}

	ABaseAIController* controller = Cast<ABaseAIController>(GetController());
	UBlackboardComponent* Board = controller->GetBlackboardComponent();

	Board->ClearValue(FName("CanCharge"));

	return true;
}

bool AChargeAIBoss::SpecialActionCall()
{
	if (!IsValid(AnimGraph))
	{
		return false;
	}

	AnimGraph->PlaySpecialAction();
	return true;
}

bool AChargeAIBoss::CanPhaseTwo()
{
	return (UnitHealth <= (UnitMaxHealth * 0.5f));
}

bool AChargeAIBoss::CurrentCharging()
{
	return IsCharging;
}

FVector AChargeAIBoss::GetHomeLocation()
{
	return HomeLocation;
}


float AChargeAIBoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//do not call super

	return 0.0f;
}

void AChargeAIBoss::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (IsDead || !IsCharging)
		return;

	ACharacter* player = Cast<ACharacter>(OtherActor);

	if (IsValid(player))
	{
		UE_LOG(LogTemp, Warning, TEXT("valid Player"));
		//Deal Damage to player
		FDamageEvent dmgEvent = FDamageEvent();
		player->TakeDamage(AttackDamage, dmgEvent, this->GetInstigatorController(), this);
		ABaseCharacter* pushme = Cast<ABaseCharacter>(player);
		if (IsValid(pushme))
		{
			UE_LOG(LogTemp, Warning, TEXT("push Player"));
			pushme->PushVector(Pushbackstrength, GetActorLocation());			
		}

		EndAttackCall();
	}
	else if((OtherComp->GetCollisionObjectType() != ECollisionChannel::ECC_GameTraceChannel2)) //may need to add an if statement to check if is pillar.
	{
		//deal damage to self
		UE_LOG(LogTemp, Warning, TEXT("INVALID Player"));

		AnimGraph->ActivateHurt();
		UnitHealth -= AttackDamage;
		FDamageEvent dmgEvent = FDamageEvent();
		OtherActor->TakeDamage(0, dmgEvent, this->GetInstigatorController(), this);



			ABaseAIController* controller = Cast<ABaseAIController>(GetController());
			UBlackboardComponent* Board = controller->GetBlackboardComponent();

			if (CanPhaseTwo())
			{
				Board->SetValueAsBool(FName("NextPhase"), true);
			}
			else 
			{
				ChargeSpeedMultiplier *= 1.5f;
				AccelMultiplier *= 1.5f;
			}

		if (UnitHealth <= 0.f)
		{
			

			if (IsValid(Board))
			{
				IsDead = true;
				UnitHealth = 0.f;
				OnAIDeath.Broadcast(-1);
				AnimGraph->DeathState(IsDead);
				controller->StopMovement();
				controller->UnPossess();
				controller->Destroy();
				//UE_LOG(LogTemp, Error, TEXT("AI DEAD"));
				KillEnemy();
			}
			
		}
		EndAttackCall();
	}

	
}

bool AChargeAIBoss::PlayEnemyCall(USoundBase* sound)
{
	UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	return true;
}
