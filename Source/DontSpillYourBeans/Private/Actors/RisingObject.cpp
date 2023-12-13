// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RisingObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AI/Characters/BaseAICharacter.h"
#include "AI/Characters/ChargeAIBoss.h"
#include "TimerManager.h"

// Sets default values
ARisingObject::ARisingObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	boxCollider->SetupAttachment(MeshComp);



}

float ARisingObject::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDestructable)
	{
		if (CanEnemy)
		{
			ABaseAICharacter* enemy = Cast<ABaseAICharacter>(DamageCauser);
			//UE_LOG(LogTemp, Warning, TEXT("hit"));
			if (IsValid(enemy))
			{
				//UE_LOG(LogTemp, Warning, TEXT("enemy"));

				AChargeAIBoss* Boss = Cast<AChargeAIBoss>(DamageCauser);

				if (IsValid(Boss))
				{
					//UE_LOG(LogTemp, Warning, TEXT("Boss"));
					if (Boss->CurrentCharging())
					{
						//UE_LOG(LogTemp, Warning, TEXT("Charging"));
						this->Destroy();
						return 0.0f;
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("NOT Boss"));
					this->Destroy();
					return 0.0f;
				}
			}
		}

		if (CanPlayer)
		{
			//Add in player stuff
			return 0.0f;
		}
	}

	return 0.0f;
}

// Called when the game starts or when spawned
void ARisingObject::BeginPlay()
{
	Super::BeginPlay();
	/*boxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);*/
	FVector CurrPosition = GetActorLocation();
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ARisingObject::OnCollisionBegin);
	if (zMovement > 0)
		EndLoc.Z = CurrPosition.Z + Range;
	else
		EndLoc.Z = CurrPosition.Z - Range;
	DelayToggle = true;
}

void ARisingObject::MovePlatform(float DeltaTime)
{
	FVector NewPos = GetActorLocation();

	if (EndLoc.Z > NewPos.Z)
	{
		NewPos.Z += zMovement;
	}
	else
	{
		if (!isColliding)
		{
			isColliding = true;
			boxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}

		return;
	}


	SetActorLocation(NewPos);
}

void ARisingObject::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Box"));
	if (IsDestructable)
	{
		/*ABaseAICharacter* enemy = Cast<ABaseAICharacter>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("hit"));
		if (IsValid(enemy))
		{
			UE_LOG(LogTemp, Warning, TEXT("enemy"));

			AChargeAIBoss* Boss = Cast<AChargeAIBoss>(OtherActor);

			if (IsValid(Boss))
			{
				UE_LOG(LogTemp, Warning, TEXT("Boss"));
				if (Boss->CurrentCharging())
				{
					UE_LOG(LogTemp, Warning, TEXT("Charging"));
					this->Destroy();
				}				
			}
			else 
			{
				UE_LOG(LogTemp, Warning, TEXT("NOT Boss"));
				this->Destroy();
			}*/

		//}

	}
}

// Called every frame
void ARisingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DelayToggle)
	{
		FTimerHandle handler;
		//UE_LOG(LogTemp, Warning, TEXT("Time: %f"), DelayTime);
		GetWorld()->GetTimerManager().SetTimer(handler, [&]() { DelayToggle = false; }, DelayTime, false);
	}
	else
	{
		if (!isColliding && !DelayToggle)
			MovePlatform(DeltaTime);
	}
}

