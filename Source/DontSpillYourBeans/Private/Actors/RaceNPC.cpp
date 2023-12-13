// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RaceNPC.h"
#include "Actors/PatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"

ARaceNPC::ARaceNPC()
{


}

FVector ARaceNPC::GetNextPoint()
{

	FVector point = FVector();

	if (CurrentPoint < Points.Num())
	{
		if (CurrentPoint == 0 && IsLap)
		{
			CurrentLap++;
			IsLap = false;

			if (CurrentLap >= MaxLaps)
			{
				IsRacerFinished = true;
				IsRacerReady = false;

				ABaseAIController* RaceController = Cast<ABaseAIController>(GetController());
				if (IsValid(RaceController))
				{
					UBlackboardComponent* Board = RaceController->GetBlackboardComponent();
					if (IsValid(Board))
					{
						Board->SetValueAsBool(FName("Finished"), IsRacerFinished);
						Board->SetValueAsBool(FName("Ready"), IsRacerReady);
					}
				}
			}
		}

		 point = Points[CurrentPoint]->GetActorLocation();
		CurrentPoint++;
	}
	else
	{
		CurrentPoint = 0;
		point = Points[CurrentPoint]->GetActorLocation();
		IsLap = true;
	}
	

	return point;
}

void ARaceNPC::AcceptQuest()
{
	Super::AcceptQuest();

	ABaseAIController* RaceController = Cast<ABaseAIController>(GetController());
	if (IsValid(Controller) && !IsRacerFinished)
	{
		UBlackboardComponent* Board = RaceController->GetBlackboardComponent();
		if (IsValid(Board))
		{
			Board->SetValueAsVector(FName("TagetLocation"), HomeLocation);
			IsRacerReady = true;
			Board->SetValueAsBool(FName("Ready"), IsRacerReady);
			UE_LOG(LogTemp, Warning, TEXT("Lets Race!"))
				OnReady.Broadcast();
		}
	}
	
}

bool ARaceNPC::ReachedLastPoint()
{
	return (CurrentPoint == (Points.Num() - 1));
}

void ARaceNPC::BeginPlay()
{
	Super::BeginPlay();

	CurrentPoint = 0;
	IsRacerReady = false;
	IsRacerFinished = false;
	HomeLocation = GetActorLocation();
}

void ARaceNPC::OnInteract()
{
	Super::OnInteract();

}
