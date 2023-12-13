// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseMovingPlatform.h"
#include "TimerManager.h"


// Sets default values
ABaseMovingPlatform::ABaseMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	delayToggle = false;
	HandleCheck = true;
}

// Called when the game starts or when spawned
void ABaseMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	FVector CurrPosition = GetActorLocation();

	if (MovementDirection.xMovement != 0)
	{
		if (MovementDirection.xMovement > 0)
			EndLoc.X = CurrPosition.X + Range;
		else
			EndLoc.X = CurrPosition.X - Range;

		StartLoc.X = CurrPosition.X;
	}

	if (MovementDirection.zMovement != 0)
	{
		if (MovementDirection.zMovement > 0)
			EndLoc.Z = CurrPosition.Z + Range;
		else
			EndLoc.Z = CurrPosition.Z - Range;

		StartLoc.Z = CurrPosition.Z;
	}

	if (MovementDirection.yMovement != 0)
	{
		if (MovementDirection.yMovement > 0)
			EndLoc.Y = CurrPosition.Y + Range;
		else
			EndLoc.Y = CurrPosition.Y - Range;

		StartLoc.Y = CurrPosition.Y;
	}
}


// Called every frame
void ABaseMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DelayTime > 0)
	{
		if (delayToggle && HandleCheck)
		{
			FTimerHandle handler;
			HandleCheck = false;
			GetWorld()->GetTimerManager().SetTimer(handler, [&]() { delayToggle = false; HandleCheck = true; }, DelayTime, false);
		}

	}

	MovePlatform(DeltaTime);



}

void ABaseMovingPlatform::MovePlatform(float DeltaTime)
{

	if (delayToggle)
		return;

	FVector NewPos = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("-----TOP-----"));
	if ((NewPos.X > EndLoc.X && MovementDirection.xMovement > 0) || (NewPos.X < EndLoc.X && MovementDirection.xMovement < 0))
	{
		Toggle = true;
		delayToggle = true;
		//UE_LOG(LogTemp, Warning, TEXT("Toggle True, End: %f, X: %f"), EndLoc.X, NewPos.X);
	}
	else if ((NewPos.X < StartLoc.X && MovementDirection.xMovement > 0) || (NewPos.X > StartLoc.X && MovementDirection.xMovement < 0))
	{
		Toggle = false;
		delayToggle = true;
		//UE_LOG(LogTemp, Warning, TEXT("Toggle false, End: %f, X: %f"), EndLoc.X, NewPos.X);
	}

	if (!Toggle && MovementDirection.xMovement != 0)
	{
		NewPos.X += MovementDirection.xMovement;
		//UE_LOG(LogTemp, Warning, TEXT("X Addition: %f"), NewPos.X);
	}
	else if (Toggle && MovementDirection.xMovement != 0)
	{
		NewPos.X -= MovementDirection.xMovement;
		//UE_LOG(LogTemp, Warning, TEXT("X Subtraction: %f"), NewPos.X);
	}
	//UE_LOG(LogTemp, Warning, TEXT("-----BOTTOM-----"));


	if ((NewPos.Z > EndLoc.Z && MovementDirection.zMovement > 0) || (NewPos.Z < EndLoc.Z && MovementDirection.zMovement < 0))
	{
		Toggle = true;
		delayToggle = true;
	}
	else if ((NewPos.Z < StartLoc.Z && MovementDirection.zMovement > 0) || (NewPos.Z > StartLoc.Z && MovementDirection.zMovement < 0))
	{
		Toggle = false;
		delayToggle = true;
	}

	if (!Toggle && MovementDirection.zMovement != 0)
	{
		NewPos.Z += MovementDirection.zMovement;
	}
	else if (Toggle && MovementDirection.zMovement != 0)
	{
		NewPos.Z -= MovementDirection.zMovement;
	}



	if ((NewPos.Y > EndLoc.Y && MovementDirection.yMovement > 0) || (NewPos.Y < EndLoc.Y && MovementDirection.yMovement < 0))
	{
		Toggle = true;
		delayToggle = true;
	}
	else if ((NewPos.Y < StartLoc.Y && MovementDirection.yMovement > 0) || (NewPos.Y > StartLoc.Y && MovementDirection.yMovement < 0))
	{
		Toggle = false;
		delayToggle = true;
	}

	if (!Toggle && MovementDirection.yMovement != 0)
	{
		NewPos.Y += MovementDirection.yMovement;
	}
	else if (Toggle && MovementDirection.yMovement != 0)
	{
		NewPos.Y -= MovementDirection.yMovement;
	}

	SetActorLocation(NewPos);

	CurrTime += DeltaTime;


}

