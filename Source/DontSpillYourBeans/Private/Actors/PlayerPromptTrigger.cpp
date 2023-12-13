// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerPromptTrigger.h"
#include "Pawn/InventoryPlayer.h"
#include "Interface/PlayerPromptWidget.h"

// Sets default values
APlayerPromptTrigger::APlayerPromptTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereCollider->SetupAttachment(GetRootComponent());
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerPromptTrigger::OnCollisionBegin);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &APlayerPromptTrigger::OnCollisionEnd);

	shown = false;

}

// Called when the game starts or when spawned
void APlayerPromptTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPromptTrigger::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!shown)
	{
		AInventoryPlayer* inventoryPlayer = Cast<AInventoryPlayer>(OtherActor);

		if (!IsValid(inventoryPlayer))
		{
			return;
		}

		//Set Text Values to values passed in the blueprint
		inventoryPlayer->WC_PlayerPrompt->title->SetText(TitleTxt);
		inventoryPlayer->WC_PlayerPrompt->prompt->SetText(PromptTxt);

		//Add to the players viewport, enable mouse input, and disable player rotation.
		inventoryPlayer->WC_PlayerPrompt->Show();

		shown = true;
	}
}

void APlayerPromptTrigger::OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*AInventoryPlayer* inventoryPlayer = Cast<AInventoryPlayer>(OtherActor);

	if (!IsValid(inventoryPlayer))
	{
		return;
	}

	inventoryPlayer->WC_PlayerPrompt->Hide();*/
}

// Called every frame
void APlayerPromptTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

