// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DamageProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AI/Characters/BaseAICharacter.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
ADamageProjectile::ADamageProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collider and Mesh creation
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->SetupAttachment(SphereComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamageProjectile::OnCollisionBegin);

	//Projectile Comp
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileComponent->InitialSpeed = BaseSpeed;
	ProjectileComponent->MaxSpeed = MaxSpeed;
	//ProjectileComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ADamageProjectile::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Handler;
	//UE_LOG(LogTemp, Warning, TEXT("Spawned!"));
	GetWorld()->GetTimerManager().SetTimer(Handler, [&]() {if (IsValid(this)) { Destroy(); }}, lifeSpan, false);

}

// Called every frame
void ADamageProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageProjectile::SetDropRate(float DropAmount, FVector TargetLocation, FVector TargetVelocity)
{
	//UE_LOG(LogTemp, Warning, TEXT("DropRate: %f"), DropAmount);

	FVector NewVelocity = TargetVelocity * (DropAmount / BaseSpeed);
	FVector NewTargetLocation = TargetLocation + NewVelocity;
	FVector TossVelocity;

	UE_LOG(LogTemp, Warning, TEXT("NTL:: (%f, %f, %f)"), NewTargetLocation.X, NewTargetLocation.Y, NewTargetLocation.Z);
	bool fart = UGameplayStatics::SuggestProjectileVelocity(GetWorld(), TossVelocity, GetActorLocation(), NewTargetLocation, BaseSpeed, false,
		0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), true);


	UE_LOG(LogTemp, Warning, TEXT("TOS:: (%f, %f, %f)"), TossVelocity.X, TossVelocity.Y, TossVelocity.Z);

	if (!fart)
		UE_LOG(LogTemp, Warning, TEXT("TOSS is False"));

	ProjectileComponent->Velocity = TossVelocity;
	ProjectileComponent->bRotationFollowsVelocity = true;

	//Old Code Delete Later
#pragma region Old
	//if (DropAmount > 768)
	//{
	//	ProjectileComponent->ProjectileGravityScale = (1000 / DropAmount);
	//}
	//else if (DropAmount > 517)
	//{
	//	ProjectileComponent->ProjectileGravityScale = (100 / DropAmount) * 15;
	//}
	//else
	//{
	//	ProjectileComponent->ProjectileGravityScale = (100 / DropAmount) * 25;
	//}
#pragma endregion


}

void ADamageProjectile::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ABaseAICharacter* enemy = Cast<ABaseAICharacter>(OtherActor);
	ADamageProjectile* bullet = Cast<ADamageProjectile>(OtherActor);
	if (IsValid(enemy) || IsValid(bullet))
		return;

	if (IsValid(splat))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), splat, GetActorLocation());


	//UE_LOG(LogTemp, Warning, TEXT("Collision"));

	FDamageEvent dmgEvent = FDamageEvent();
	OtherActor->TakeDamage(damage, dmgEvent, this->GetInstigatorController(), this);
	StaticMeshComponent->Deactivate();
	FTimerHandle handler;
	GetWorld()->GetTimerManager().SetTimer(handler, [&]() {Destroy(); }, 1, false);
}

