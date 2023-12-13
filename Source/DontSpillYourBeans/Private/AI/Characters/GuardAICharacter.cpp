// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Characters/GuardAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"
#include "Pawn/BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AGuardAICharacter::AGuardAICharacter()
{

}

bool AGuardAICharacter::AttackCall()
{
	Super::AttackCall();
	PlayAttackAudio();
	return true;
}

float AGuardAICharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GetDirection() == 0.0f)
		Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void AGuardAICharacter::BeginPlay()
{
	Super::BeginPlay();

	ABaseAIController* controller = Cast<ABaseAIController>(GetController());

	if (IsValid(controller))
	{
		controller->SaveGuardLocation(GetActorLocation());
		controller->SetGuardLocation();
	}
	TrailZSpawn = 250;
}

float AGuardAICharacter::GetDirection()
{
	ABaseAIController* MyController = Cast<ABaseAIController>(GetController());
	if (!IsValid(MyController))
		return 0.0f;

	UBlackboardComponent* MyBoard = MyController->GetBlackboardComponent();
	if (!IsValid(MyBoard))
		return 0.0f;

	ABaseCharacter* player = Cast<ABaseCharacter>(MyBoard->GetValueAsObject(FName("Player")));
	if (!IsValid(player))
		return 0.0f;


	FVector PlayerLocation = player->GetActorLocation();
	PlayerLocation.Normalize();
	FVector MyLocation = GetActorLocation();
	MyLocation.Normalize();

	FRotator direction = UKismetMathLibrary::FindLookAtRotation(MyLocation, PlayerLocation);

	UKismetMathLibrary::GetDirectionUnitVector(MyLocation, PlayerLocation);
	UE_LOG(LogTemp, Warning, TEXT("X Rotation: %f | Y Rotation: %f | Z Rotation: %f"), direction.Roll, direction.Pitch, direction.Yaw);

	return 1.0f;
}

FVector AGuardAICharacter::GetGuardPoint()
{
	return GetActorLocation();
}
