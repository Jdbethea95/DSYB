// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/ShopKeepAnimation.h"
#include "TimerManager.h"

void UShopKeepAnimation::NativeUpdateAnimation(float DeltaSeconds)
{

}

void UShopKeepAnimation::WakeUpShopKeep()
{

	if (GetWorld()->GetTimerManager().IsTimerActive(handler))
	{

		GetWorld()->GetTimerManager().ClearTimer(handler);
	}
		
	GetWorld()->GetTimerManager().SetTimer(handler, [&]() 
		{ 
			
			if (WakeSpeed < 100)
			{
				WakeSpeed += 1.0f;
			}
			else
			{
				WakeSpeed = 100;
			}

		}, 0.01f, true);
}

void UShopKeepAnimation::SleepNowShopKeep()
{

	if (GetWorld()->GetTimerManager().IsTimerActive(handler))
	{

		GetWorld()->GetTimerManager().ClearTimer(handler);
	}

	GetWorld()->GetTimerManager().SetTimer(handler, [&]() 
		{ 
			if (WakeSpeed > 1)
			{
				WakeSpeed -= 1.0f;
			}
			else
			{
				WakeSpeed = 0;
			}

		}, 0.01f, true);
}
