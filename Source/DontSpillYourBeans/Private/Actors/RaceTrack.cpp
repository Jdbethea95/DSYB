// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RaceTrack.h"
#include "Components/BoxComponent.h"
#include "Pawn/BaseCharacter.h"
#include "Interface/RaceWidget.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ARaceTrack::ARaceTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


void ARaceTrack::StartRace()
{
	if (!CheckPoints.IsEmpty())
	{
		CheckPoints[0]->BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CheckPoints[0]->ToggleGate(true);
	}
}

// Called when the game starts or when spawned
void ARaceTrack::BeginPlay()
{
	Super::BeginPlay();
	ToggleCollision();
	


}

void ARaceTrack::UpdateCheckPoints(int ID, ABaseCharacter* player)
{ //this works because the checkpoint IDs' start at 1

	if (ID < CheckPoints.Num())
	{
		if (IsLap && ID == 1)
		{
			CurrentLap++;
			IsLap = false;
			UE_LOG(LogTemp, Warning, TEXT("LAP: %d out of %d"), CurrentLap, MaxLaps);
			FString LapPrint = FString::FromInt(CurrentLap) + "/" + FString::FromInt(MaxLaps);
	
			WC_RaceWidget->LapCount->SetText(FText::FromString(LapPrint));
			if (CurrentLap >= MaxLaps)
			{
				UE_LOG(LogTemp, Warning, TEXT("FINISH LINE!"), CurrentLap, MaxLaps);

				if (racer->IsRacerFinished)
				{
					UE_LOG(LogTemp, Warning, TEXT("You Lost!"), CurrentLap, MaxLaps);
					WC_RaceWidget->LapCount->SetText(FText::FromString("You"));
					WC_RaceWidget->LapTitle->SetText(FText::FromString("Lost?"));
					WC_RaceWidget->HideLaps();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("You Won!"), CurrentLap, MaxLaps);
					WC_RaceWidget->LapCount->SetText(FText::FromString("You"));
					WC_RaceWidget->LapTitle->SetText(FText::FromString("Won!"));
					WC_RaceWidget->HideLaps();
				}

				CheckPoints[ID - 1]->BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				CheckPoints[ID - 1]->ToggleGate(false);
				return;
			}
		}

		CheckPoints[ID]->BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CheckPoints[ID]->ToggleGate(true);
		CheckPoints[ID - 1]->BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CheckPoints[ID - 1]->ToggleGate(false);
	}
	else
	{
		CheckPoints[0]->BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CheckPoints[0]->ToggleGate(true);
		CheckPoints[ID - 1]->BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CheckPoints[ID - 1]->ToggleGate(false);
		IsLap = true;
	}

}

void ARaceTrack::ToggleCollision()
{
	for (size_t i = 0; i < CheckPoints.Num(); i++)
	{

			//turn off colliders
			CheckPoints[i]->BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			CheckPoints[i]->ToggleGate();


		CheckPoints[i]->OnCheckHit.AddDynamic(this, &ARaceTrack::UpdateCheckPoints);
	}

	if (IsValid(racer))
	{
		racer->OnReady.AddDynamic(this, &ARaceTrack::StartRace);
		racer->OnReady.AddDynamic(this, &ARaceTrack::WidgetSetup);
	}
}

void ARaceTrack::WidgetSetup()
{
	if (!IsValid(WC_RaceWidget))
	{
		APlayerController* myPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (IsValid(myPlayerController))
		{
			WC_RaceWidget = CreateWidget<URaceWidget>(myPlayerController, TSub_Widget);
			WC_RaceWidget->AddToViewport(0);
			UE_LOG(LogTemp, Error, TEXT("Widget Made"));
			FString LapPrint = FString::FromInt(CurrentLap) + "/" + FString::FromInt(MaxLaps);
			WC_RaceWidget->LapCount->SetText(FText::FromString(LapPrint));
			WC_RaceWidget->ShowLaps();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Widget Made"));
		FString LapPrint = FString::FromInt(CurrentLap) + "/" + FString::FromInt(MaxLaps);
		WC_RaceWidget->LapCount->SetText(FText::FromString(LapPrint));
		WC_RaceWidget->ShowLaps();
	}
}


