// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Drops/ItemProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Actors/PickupObjectShell.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
AItemProjectile::AItemProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->SetupAttachment(SphereComponent);

	//Projectile Comp
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
}

bool AItemProjectile::ShootItem(FVector OwnerLocation, FVector OwnerVelocity)
{	//Owner is the AI, in a projectile targeting soming this would be the player

	FVector NewLocation = OwnerLocation; //this becomes our target location
	NewLocation.X += FMath::RandRange(MinDistance, MaxDistance);
	NewLocation.Y += FMath::RandRange(MinDistance, MaxDistance);
		

	float distance = FVector::Dist(GetActorLocation(), NewLocation);
	FVector NewVelocity = OwnerVelocity * (distance / BaseSpeed);

	FVector NewTargetLocation = NewLocation * NewVelocity;
	FVector TossVelocity;
	bool fart = UGameplayStatics::SuggestProjectileVelocity(GetWorld(), TossVelocity, GetActorLocation(), NewLocation, BaseSpeed, true,
		0.0f, 0.0f, ESuggestProjVelocityTraceOption::TraceFullPath, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), false);

	UE_LOG(LogTemp, Warning, TEXT("TOS:: (%f, %f, %f)"), TossVelocity.X, TossVelocity.Y, TossVelocity.Z);

	if (!fart)
		UE_LOG(LogTemp, Warning, TEXT("TOSS is False"));

	ProjectileComponent->Velocity = TossVelocity;
	ProjectileComponent->bRotationFollowsVelocity = true;

	return false;
}

// Called when the game starts or when spawned
void AItemProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemProjectile::OnCollisionBegin);

	ProjectileComponent->InitialSpeed = BaseSpeed;
	ProjectileComponent->MaxSpeed = MaxSpeed;
	hasSpawned = false;
	FTimerHandle Handler;
	//UE_LOG(LogTemp, Warning, TEXT("Spawned!"));
	GetWorld()->GetTimerManager().SetTimer(Handler, [&]() {if (IsValid(this)) { Destroy(); }}, lifeSpan, false);

}

void AItemProjectile::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Items.IsEmpty())
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Collision on trail!"));

	int indx = FMath::RandRange(0, Items.Num() - 1);

	if (indx >= Items.Num())
		return;

	if (!hasSpawned && !OtherActor->Tags.IsEmpty() && OtherActor->Tags[0] == FName("Ground"))
	{
		hasSpawned = true;
		FVector location = GetActorLocation();
		location.Z += 50;
		GetWorld()->SpawnActor<AActor>(Items[indx], location, FRotator(0, 0 ,0));
		Destroy();

	}




}

// Called every frame
void AItemProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

