// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SwordActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "AI/Characters/BaseAICharacter.h"
#include "Pawn/BaseCharacter.h"

// Sets default values
ASwordActor::ASwordActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StereoSystem = CreateDefaultSubobject<UAudioComponent>(TEXT("StereoComponent"));
	StaticMeshComponent->SetupAttachment(SphereComponent);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASwordActor::OnCollisionBegin);

	StaticMeshComponent->SetCollisionProfileName("NoCollision");
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	isSwinging = false;
	PassOnValue = -1;
}

float ASwordActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Error, TEXT("Went INTO Sword"));
	return 0.0f;
}

void ASwordActor::SetSwordDamage(float Damage)
{
	SwordDamage = Damage;
}

void ASwordActor::ActivateSword()
{
	//if (!SphereComponent->IsActive())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Sword Active"));
	//	SphereComponent->Activate(); //to later be called by an animNotify
	//}

}

void ASwordActor::SetSwordOwner(AActor* owner)
{
	if (IsValid(owner))
		SwordOwner = owner;
}

AActor* ASwordActor::GetSwordOwner()
{
	if (IsValid(SwordOwner))
		return SwordOwner;
	else
		return nullptr;
}

// Called when the game starts or when spawned
void ASwordActor::BeginPlay()
{
	Super::BeginPlay();
	if (SphereComponent->IsActive())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Sword Deactivated"));
		//SphereComponent->Deactivate();
	}

}

bool ASwordActor::PlayWhackCall(USoundBase* sound)
{
	UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	return true;
}

void ASwordActor::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!isSwinging)
	{
		return;
	}

	int indx = FMath::RandRange(0, WhackSounds.Num() - 1);
	ABaseCharacter* player = Cast<ABaseCharacter>(OtherActor);
	
	if (IsValid(player))
	{
		return;
	}

	StereoSystem->Sound = WhackSounds[indx];
	if (!StereoSystem->IsPlaying())
	{
		StereoSystem->Play();
	}
	//PlayWhackCall();

	//UE_LOG(LogTemp, Warning, TEXT("Sword Collision"));
	ABaseAICharacter* enemy = Cast<ABaseAICharacter>(OtherActor);
	if (IsValid(enemy))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Enemy Collision"));
		FDamageEvent dmgEvent = FDamageEvent();
		if (enemy->IsAlive())
			OtherActor->TakeDamage(SwordDamage, dmgEvent, this->GetInstigatorController(), this);

		OnPlayerAttack.Broadcast();
	}


}

void ASwordActor::SwingSword()
{
	isSwinging = true;
}

void ASwordActor::StopSword()
{
	isSwinging = false;
}



