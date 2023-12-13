// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/PortalManager.h"
#include "Actors/TeleportActor.h"
#include "Interface/ProtalList.h"
#include "Components/ScrollBox.h"
#include "Interface/PortalObject.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Interface/TextButtonWithIntWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortalManager::APortalManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortalManager::BeginPlay()
{
	Super::BeginPlay();

	SetUpPortals();
	SetUpListWidget();
	Teleporting = false;
}

void APortalManager::SetUpPortals()
{

	for (size_t i = 0; i < Portals.Num(); i++)
	{
		Portals[i]->PortalID = i; //most likely not needed, but just in case.
		Portals[i]->OnActivate.AddDynamic(this, &APortalManager::SetCurrentPad);
		Portals[i]->OnActivate.AddDynamic(this, &APortalManager::AddPortalToList);
		Portals[i]->OnDeactivate.AddDynamic(this, &APortalManager::RemoveCurrentPad);
	}

}

void APortalManager::SetUpListWidget()
{
	if (!IsValid(WC_PortalList))
	{
		APlayerController* myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(myPlayerController))
		{
			WC_PortalList = CreateWidget<UProtalList>(myPlayerController, SubListClass);
			WC_PortalList->AddToViewport(0);
			WC_PortalList->HideList();
			WC_PortalList->ExitButton->OnClicked.AddDynamic(this, & APortalManager::CloseList);
		}
	}
}

void APortalManager::TeleportPlayer(int index)
{

	//UE_LOG(LogTemp, Error, TEXT("Teleporting %d"), index);

	APlayerController* myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(myPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Movement = false"));
		myPlayerController->SetIgnoreMoveInput(false);
		Teleporting = true;
	}

	if (IsValid(CurrentPortal))
	{
		//UE_LOG(LogTemp, Error, TEXT("Current is Valid"));
		activePortals[index]->bJustPorted = true;
		CurrentPortal->SetDestination(activePortals[index]);
		CurrentPortal->TeleportPlayer();
		Teleporting = false;
		if (IsValid(WC_PortalList))
		{
			WC_PortalList->HideList();
		}
	}
}

void APortalManager::SetCurrentPad(ATeleportActor* CurrPortal, int ID)
{
	CurrentPortal = CurrPortal;

	if (!Teleporting)
	{
		APlayerController* myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(myPlayerController))
		{
			UE_LOG(LogTemp, Error, TEXT("Movement = true"));
			myPlayerController->SetIgnoreMoveInput(true);
		}
	}else if(Teleporting)
	{
		Teleporting = false;
	}

	if (IsValid(WC_PortalList))
	{
		WC_PortalList->ShowList();
	}
}

void APortalManager::RemoveCurrentPad()
{
	if (IsValid(CurrentPortal))
	{
		//CurrentPortal = nullptr;
	}
}

void APortalManager::AddPortalToList(ATeleportActor* CurrPortal, int ID)
{

	WC_PortalObject = CreateWidget<UPortalObject>(GetWorld(), EntryObject);

	if (IsValid(WC_PortalObject) && !CurrentPortal->bisUnlocked)
	{


		WC_PortalList->PortalListView->AddChild(WC_PortalObject);
		WC_PortalObject->PortalButton->buttonTextBlock->SetText(Portals[ID]->Title);
		WC_PortalObject->PortalButton->OnPassNumber.AddDynamic(this, &APortalManager::TeleportPlayer);
		CurrentPortal->bisUnlocked = true;
		activePortals.Add(CurrentPortal);
		WC_PortalObject->PortalButton->number = activePortals.IndexOfByKey(CurrentPortal);
	}
}

void APortalManager::CloseList()
{
	Teleporting = false;
	APlayerController* myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(myPlayerController))
	{
		myPlayerController->SetIgnoreMoveInput(false);
	}

	WC_PortalList->HideList();

}

// Called every frame
void APortalManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

