// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalManager.generated.h"

class ATeleportActor;
class UProtalList;
class UPortalObject;

UCLASS()
class DONTSPILLYOURBEANS_API APortalManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortalManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portals")
		TArray<ATeleportActor*> Portals;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portals")
		UProtalList* WC_PortalList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portals")
		TSubclassOf<UProtalList> SubListClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "List Entry")
		TSubclassOf<UPortalObject> EntryObject;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portals")
		UPortalObject* WC_PortalObject;

	ATeleportActor* CurrentPortal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<ATeleportActor*> activePortals;
	bool Teleporting;
	void SetUpPortals();
	void SetUpListWidget();

	UFUNCTION()
		void TeleportPlayer(int index);

	UFUNCTION()
		void SetCurrentPad(ATeleportActor* CurrPortal, int ID);
	UFUNCTION()
		void RemoveCurrentPad();

	UFUNCTION()
		void AddPortalToList(ATeleportActor* CurrPortal, int ID);

	UFUNCTION()
		void CloseList();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
