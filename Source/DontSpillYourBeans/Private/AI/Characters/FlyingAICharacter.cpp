// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Characters/FlyingAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"
#include "Actors/DamageProjectile.h"
#include "Engine/DamageEvents.h"
#include "TimerManager.h"

AFlyingAICharacter::AFlyingAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SphereComponent->SetupAttachment(GetMesh());

	IsDead = false;
	ShootToggle = true;
	deltaSum = 1;
}



void AFlyingAICharacter::BeginPlay()
{
	Super::BeginPlay();

	//lifting the mesh up
	LandedPos = GetMesh()->GetRelativeLocation().Z;
	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y,
		FlyingOffset));

	//Setting upper bounds for the mesh and bobbing
	ArielPos = GetMesh()->GetRelativeLocation().Z;
	upper = GetMesh()->GetRelativeLocation().Z + BobLimit;

	//setting lower bounds for mesh and bobbing.
	lower = GetMesh()->GetRelativeLocation().Z - BobLimit;

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AFlyingAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ShootToggle prevents the bobble effect in instances it cant shoot, aka not at full height.
	Bobble(DeltaTime, ShootToggle);

	if (LandToggle)
	{
		Land(DeltaTime);
	}
	else
	{
		Rise(DeltaTime);
	}
}

//Flight Functions
bool AFlyingAICharacter::Bobble(float alpha, bool trigger)
{

	if (!trigger)
		return false;

	float movement = GetMesh()->GetRelativeLocation().Z; //just in case

	if (!bobbleToggle)
	{
		alphaSum += (alpha * BobSpeed);
		movement = FMath::Lerp(GetMesh()->GetRelativeLocation().Z, upper, alphaSum);

		if (alphaSum >= 1)
		{
			//lerp is based on alpha, closer to 0 mean closer to the A param, closer to 1 means closer to B param;
				//so to transition between them smoothly we use DeltaTime to increment to the 1;
			bobbleToggle = true;
			//alphaSum = 0;
			//UE_LOG(LogTemp, Warning, TEXT("Toggled Bobble UP: %f"), alphaSum);
		}

	}
	else
	{
		alphaSum -= (alpha * BobSpeed);
		if (alphaSum <= 0)
		{
			bobbleToggle = false;
			alphaSum = 0;
			//UE_LOG(LogTemp, Warning, TEXT("Toggled Bobble DOWN: %f"), alphaSum);
		}

		movement = FMath::Lerp(lower, GetMesh()->GetRelativeLocation().Z, alphaSum);

	}

	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, movement));
	return true;
}

bool AFlyingAICharacter::Land(float alpha)
{

	float movement = 0.f;//GetMesh()->GetRelativeLocation().Z;

	deltaSum -= (alpha * LandSpeed);
	if (deltaSum <= 0)
	{
		deltaSum = 0;

		//Waits LandedTime in Seconds Before Toggling To Rise again.
		FTimerHandle Handler;
		GetWorld()->GetTimerManager().SetTimer(Handler, [&]() {LandToggle = false; }, LandedTime, false);
	}

	movement = FMath::Lerp(LandedPos, GetMesh()->GetRelativeLocation().Z, deltaSum);
	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, movement));
	return true;
}

bool AFlyingAICharacter::Rise(float alpha)
{
	if (IsDead || ShootToggle)
	{
		return false;
	}

	float movement = GetMesh()->GetRelativeLocation().Z;

	deltaSum += (alpha * LandSpeed);
	movement = FMath::Lerp(GetMesh()->GetRelativeLocation().Z, ArielPos, deltaSum);

	if (deltaSum >= 1)
	{
		ShootToggle = true;
	}
	PlayMovementAudio();
	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, movement));
	return true;
}


//Attack Functions
float AFlyingAICharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//UE_LOG(LogTemp, Warning, TEXT("HIT THE FLIER"));

	if (IsDead || ShootToggle)
		return 0.f;

	UnitHealth -= Damage;


	FDamageEvent dmgEvent = FDamageEvent();
	//calculate pushback
	PushbackVector = (DamageCauser->GetActorLocation() - GetActorLocation()); //a backwards velocity from the player

	PushbackVector *= (Pushbackstrength * 2);
	this->LaunchCharacter(PushbackVector, false, false);
	//UE_LOG(LogTemp, Warning, TEXT("PUSH"));

	if (UnitHealth <= 0.f)
	{
		ABaseAIController* controller = Cast<ABaseAIController>(GetController());
		if (!IsValid(controller))
			return 0.f;
		UBlackboardComponent* Board = controller->GetBlackboardComponent();
		if (!IsValid(Board))
			return 0.f;

		IsDead = true;
		UnitHealth = 0.f;
		OnAIDeath.Broadcast(-1);
		AnimGraph->DeathState(IsDead);
		PlayDeathAudio();
		controller->StopMovement();
		controller->UnPossess();
		controller->Destroy();

		DropItem();
		KillEnemy();
		return 0.0f;
	}
	else if (UnitHealth >= UnitMaxHealth)
	{
		UnitHealth = UnitMaxHealth;
		return 0.0f;
	}
	else
	{
		AnimGraph->ActivateHurt();
	}

	return 0.0f;
}

//Callable Attack task functions. Used in the Behavior tree tasks'
bool AFlyingAICharacter::AttackCall()
{
	if (!GetLandToggle())
		Shoot();
		return false;
}

bool AFlyingAICharacter::EndAttackCall()
{
	AnimGraph->DeactivateAttack();
		return true;
}

//Mechanical Attack Functions
bool AFlyingAICharacter::Shoot()
{
	if (CanShoot())
	{
		FActorSpawnParameters Params;
		Params.Owner = GetController();
		FVector Location = GetActorLocation();
		Location.Z += 500;
		FRotator Rotation = GetActorRotation();

		if (!IsValid(ProjectileRef))
		{
			//UE_LOG(LogTemp, Error, TEXT("ProjectileRef INVALID"));
			return false;
		}

		//setting bullet drop.
		ABaseAIController* controller = Cast<ABaseAIController>(GetController());
		UBlackboardComponent* Board = controller->GetBlackboardComponent();
		AActor* player = Cast<AActor>(Board->GetValueAsObject("Player"));
		float Distance = 1.f;

		if (IsValid(player))
		{
			Distance = FVector::Distance(GetActorLocation(), player->GetActorLocation());
		}

		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileRef, Location, Rotation, Params);

		if (!IsValid(Projectile))
		{
			//UE_LOG(LogTemp, Error, TEXT("Projectile Actor INVALID"));
		}
		else
		{
			ADamageProjectile* bullet = Cast<ADamageProjectile>(Projectile);
			if (IsValid(bullet))
			{
				PlayAttackAudio();
				bullet->SetDropRate(Distance, player->GetActorLocation(), player->GetVelocity());
			}
		}
		ShootCount++;
	}

	return true;
}

bool AFlyingAICharacter::CanShoot()
{
	if ((IsDead || ShootCount >= MaxShootCount) && !LandToggle)
	{
		ShootCount = 0;
		LandToggle = true;
		ShootToggle = false;
		return false;
	}
	else if (!ShootToggle) { return false; }

	return true;
}

bool AFlyingAICharacter::GetLandToggle()
{
	return LandToggle;
}

bool AFlyingAICharacter::GetShootToggle()
{
	return ShootToggle;
}


//Collision Functions
void AFlyingAICharacter::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AFlyingAICharacter::OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

