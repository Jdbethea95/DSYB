// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseNPC.h"
#include "Utility/ShopKeepAnimation.h"
#include "ShopNPC.generated.h"

/**
 *
 */
UCLASS()
class DONTSPILLYOURBEANS_API AShopNPC : public ABaseNPC
{
	GENERATED_BODY()

public:
	AShopNPC();

protected:
	virtual void BeginPlay() override;

	virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void OnInteract() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UShopKeepAnimation* KeepAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool isSleeping;
private:
	class AInventoryPlayer* player;
};
