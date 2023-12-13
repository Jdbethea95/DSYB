// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Characters/FoxNPC.h"
#include "Actors/PatrolPoint.h"
#include "Actors/PickupObjectShell.h"
#include "Components/SphereComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controllers/BaseAIController.h"

AFoxNPC::AFoxNPC()
{
}

FVector AFoxNPC::GetNextPoint()
{
	FVector newPoint;
	
	if (!Points.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("IN THE RIGHT FUNCTION"));

		float distance = (GetActorLocation() - Points[Points.Num() - 1]->GetActorLocation()).Length();
		if (CurrentPoint == Points.Num())
		{
			Destroy();
		}

		if (CurrentPoint < Points.Num())
		{
			newPoint = Points[CurrentPoint]->GetActorLocation();
			CurrentPoint++;
		}
	}

	return newPoint;
}

void AFoxNPC::BeginPlay()
{
	Super::BeginPlay();

}

void AFoxNPC::OnInteract()
{

}

void AFoxNPC::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APickupObjectShell* PickupObject = Cast<APickupObjectShell>(OtherActor);

	if (IsValid(PickupObject) && PickupObject->ItemID == GrabObject)
	{
		PickupObject->Destroy();
	}
}
