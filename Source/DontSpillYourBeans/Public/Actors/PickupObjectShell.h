// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//item related
#include "Actors/BaseItem.h"
#include "PickupObjectShell.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickSignature, int, id);

UCLASS()
class DONTSPILLYOURBEANS_API APickupObjectShell : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupObjectShell();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FPickSignature OnPickUp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Item")
		class AItemManager* PickManager;

	//Select item type in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Item")
		TSubclassOf<ABaseItem> ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Item")
		FName ItemID;

	//Audio 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|SFX")
		class USoundBase* InvalidSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|SFX")
		class USoundBase* ValidSound;

	UFUNCTION(BlueprintCallable)
		void PlaySound(USoundBase* sound);

	//Look VFX
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	//	class UParticleSystemComponent* ParticleSystem;
	
	//Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup|Colider")
		class UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Colider")
		FVector Size;

	//Pickup
	UFUNCTION(BlueprintCallable)
		void  HandlePickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//	UFUNCTION(BlueprintCallable)
	//	bool CanPickUP(AActor* OtherActor) const;

	//UFUNCTION(BlueprintCallable)
	//	bool ShouldPickUP(AActor* OtherActor) const;

	UFUNCTION(BlueprintCallable)
		void NoPickUp();

	UFUNCTION(BlueprintCallable)
		void PostPickUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup | ID")
		int ShellId;


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ABaseItem* item;
};

