// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseNPC.h"
#include "Pawn/InventoryPlayer.h"
#include "Actors/ActorComponents/QuestGiverComponent.h"
#include "Interface/DialogBoxWidget.h"
#include "Interface/QuestGiverWidget.h"
#include "QuestNPC.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API AQuestNPC : public ABaseNPC
{
	GENERATED_BODY()

public:

	AQuestNPC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UQuestGiverComponent* QuestGiverComponent;

	//Local version of the quest
	UPROPERTY()
		ABaseQuest* MyBaseQuest;

	int PreQuestDialogCounter;

	//Widgets
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UDialogBoxWidget* WC_DialogBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UQuestGiverWidget* WC_QuestGiver;
	//Widget Base Classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|Class")
		TSubclassOf<class UDialogBoxWidget> DialogBoxBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|Class")
		TSubclassOf<class UQuestGiverWidget> QuestGiverBase;
	
	virtual void OnInteract() override;

	UFUNCTION()
		void NextDialog();
	UFUNCTION()
		void ShowQuestInfo();
	UFUNCTION()
		virtual void AcceptQuest();
	UFUNCTION()
		void DeclineQuest();

protected:

	virtual void BeginPlay() override;

	virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	
	class AInventoryPlayer* player;

	void SetUpWidgets();
};
