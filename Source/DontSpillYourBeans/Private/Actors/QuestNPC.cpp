// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/QuestNPC.h"

AQuestNPC::AQuestNPC()
{
	//Setup Components
	QuestGiverComponent = CreateDefaultSubobject<UQuestGiverComponent>(TEXT("QuestGiverComponent"));

	//Default Values
	player = nullptr;
	MyBaseQuest = nullptr;
	PreQuestDialogCounter = 0;
}

void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

	MyBaseQuest = QuestGiverComponent->GetQuest();

	if (!IsValid(MyBaseQuest))
	{
		return;
	}
}

void AQuestNPC::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	player = Cast<AInventoryPlayer>(OtherActor);

	if (IsValid(player))
	{
		SetUpWidgets();
	}
	
	Super::OnCollisionBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AQuestNPC::OnInteract()
{
	if (IsInRange && IsValid(player) && IsValid(WC_DialogBox) && IsValid(WC_QuestGiver))
	{
		//If the quest is not found
		if (!MyBaseQuest->bIsKnown)
			WC_DialogBox->Show();
		else
			WC_QuestGiver->Show();
	}

}

void AQuestNPC::SetUpWidgets()
{
	//Create Widgets
	WC_DialogBox = CreateWidget<UDialogBoxWidget>(Cast<APlayerController>(player->GetController()), DialogBoxBase);
	WC_QuestGiver = CreateWidget<UQuestGiverWidget>(Cast<APlayerController>(player->GetController()), QuestGiverBase);

	if (!IsValid(WC_DialogBox) || !IsValid(WC_QuestGiver))
		return;
	else
	{
		//Dialog Box Setsup
		WC_DialogBox->BTN_NextPage->OnClicked.AddUniqueDynamic(this, &AQuestNPC::NextDialog);
		WC_DialogBox->BTN_ViewQuest->OnClicked.AddUniqueDynamic(this, &AQuestNPC::ShowQuestInfo);

		WC_DialogBox->SetIsEnabled(false);
		WC_DialogBox->SetVisibility(ESlateVisibility::Hidden);

		//Quest Giver Setup
		WC_QuestGiver->BTN_Decline->OnClicked.AddUniqueDynamic(this, &AQuestNPC::DeclineQuest);
		WC_QuestGiver->BTN_Accept->OnClicked.AddUniqueDynamic(this, &AQuestNPC::AcceptQuest);

		WC_QuestGiver->SetIsEnabled(false);
		WC_QuestGiver->SetVisibility(ESlateVisibility::Hidden);
	}

	if (!MyBaseQuest->bIsKnown)
	{
		PreQuestDialogCounter = 0;
		FText startDialog = MyBaseQuest->QuestDetails.PreQuestDialog[PreQuestDialogCounter];
		WC_DialogBox->Dialog_TXT->SetText(startDialog);

		//Widget Buttons Setup
		WC_DialogBox->BTN_NextPage->SetIsEnabled(true);
		WC_DialogBox->BTN_NextPage->SetVisibility(ESlateVisibility::Visible);
		WC_DialogBox->BTN_ViewQuest->SetIsEnabled(false);
		WC_DialogBox->BTN_ViewQuest->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AQuestNPC::NextDialog()
{
	int maxAmount = MyBaseQuest->QuestDetails.PreQuestDialog.Num();

	if (PreQuestDialogCounter + 1 < MyBaseQuest->QuestDetails.PreQuestDialog.Num())
	{
		PreQuestDialogCounter++;
		WC_DialogBox->UpdateDialog(MyBaseQuest->QuestDetails.PreQuestDialog[PreQuestDialogCounter]);
	}
	else
	{
		WC_DialogBox->BTN_NextPage->SetIsEnabled(false);
		WC_DialogBox->BTN_NextPage->SetVisibility(ESlateVisibility::Hidden);

		WC_DialogBox->BTN_ViewQuest->SetIsEnabled(true);
		WC_DialogBox->BTN_ViewQuest->SetVisibility(ESlateVisibility::Visible);
	}
}

void AQuestNPC::ShowQuestInfo()
{
	if (IsValid(WC_DialogBox) && WC_DialogBox->IsVisible())
		WC_DialogBox->Hide();

	if (IsValid(WC_QuestGiver))
	{
		WC_QuestGiver->QuestTitle_TXT->SetText(MyBaseQuest->QuestDetails.QuestName);
		WC_QuestGiver->QuestDescription_TXT->SetText(MyBaseQuest->QuestDetails.FullDescription);

		WC_QuestGiver->Show();
	}
}

void AQuestNPC::AcceptQuest()
{
	MyBaseQuest->bIsAccepted = true;
	MyBaseQuest->bIsKnown = true;
	player->QuestComponent->AddNewQuest(MyBaseQuest);
	WC_QuestGiver->Hide();
}

void AQuestNPC::DeclineQuest()
{
	MyBaseQuest->bIsKnown = true;
	WC_QuestGiver->Hide();
}


