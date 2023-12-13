// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ShopNPC.h"
#include "Pawn/InventoryPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"


AShopNPC::AShopNPC()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AShopNPC::BeginPlay()
{
	Super::BeginPlay();

	KeepAnimation = Cast<UShopKeepAnimation>(GetMesh()->GetAnimInstance());
	isSleeping = true;

	ABaseAIController* controller = Cast<ABaseAIController>(GetController());
	UBlackboardComponent* Board = controller->GetBlackboardComponent();
	Board->SetValueAsBool(FName("Sleeping"), isSleeping);
}

void AShopNPC::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	player = Cast<AInventoryPlayer>(OtherActor);

	if (IsValid(player))
	{
		KeepAnimation->WakeUpShopKeep();
		ABaseAIController* controller = Cast<ABaseAIController>(GetController());
		UBlackboardComponent* Board = controller->GetBlackboardComponent();
		isSleeping = false;
		Board->SetValueAsBool(FName("Sleeping"), isSleeping);

	}

}

void AShopNPC::OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	Super::OnCollisionEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AInventoryPlayer* leavingPlayer = Cast<AInventoryPlayer>(OtherActor);

	if (IsValid(leavingPlayer))
	{
		player->PassiveStatActor->HideShop();
		KeepAnimation->SleepNowShopKeep();
		ABaseAIController* controller = Cast<ABaseAIController>(GetController());
		UBlackboardComponent* Board = controller->GetBlackboardComponent();
		isSleeping = true;
		Board->SetValueAsBool(FName("Sleeping"), isSleeping);
	}
}

void AShopNPC::OnInteract()
{	
	if (IsInRange && IsValid(player))
	{
		player->PassiveStatActor->ShowShop();
	}
}
