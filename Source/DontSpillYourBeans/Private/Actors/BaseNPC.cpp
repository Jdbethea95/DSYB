// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseNPC.h"
#include "Interface/InteractNPCWidget.h"
#include "Pawn/InventoryPlayer.h"

// Sets default values
ABaseNPC::ABaseNPC()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereCollider->SetupAttachment(GetRootComponent());
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseNPC::OnCollisionBegin);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &ABaseNPC::OnCollisionEnd);

	InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComponent"));
	InteractWidgetComponent->SetupAttachment(GetMesh());

}

// Called when the game starts or when spawned
void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();

	InteractWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, ZOffset));
	InteractWidgetComponent->SetVisibility(false);
	IsInRange = false;
}

float ABaseNPC::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//This is here to prevent any unwanted accesses to the base TakeDamage Function.
	return 0.0f;
}

void ABaseNPC::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//Display Interact Widget Above NPC
	AInventoryPlayer* inventoryPlayer = Cast<AInventoryPlayer>(OtherActor);

	//Am I the player and not myself
	if (IsValid(inventoryPlayer))
	{
		UE_LOG(LogTemp, Warning, TEXT("INTERACTUP"));
		InteractWidgetComponent->SetVisibility(true);
		inventoryPlayer->OnInteract.AddUniqueDynamic(this, &ABaseNPC::OnInteract);
	}
	IsInRange = true;
	//Check for input from player 
	  //Maybe set a bool to let script know player is in range

}

void ABaseNPC::OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACT DOWN"));
	InteractWidgetComponent->SetVisibility(false);
	IsInRange = false;

	AInventoryPlayer* inventoryPlayer = Cast<AInventoryPlayer>(OtherActor);

	//Am I the player and not myself
	if (IsValid(inventoryPlayer))
	{
		inventoryPlayer->OnInteract.RemoveDynamic(this, &ABaseNPC::OnInteract);
	}
}

void ABaseNPC::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("F Base Pressed"));
}

// Called every frame
void ABaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

