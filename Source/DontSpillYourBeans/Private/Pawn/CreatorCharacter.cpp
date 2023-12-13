// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/CreatorCharacter.h"
#include "Components/Button.h"
#include "Interface/CharacterCreatorWidget.h"
//saving
#include "Interface/TextButtonWithIntWidget.h"
#include "Utility/MyGameInstance.h"
#include "Utility/SaveDataSaveGame.h"
ACreatorCharacter::ACreatorCharacter()
{

}

void ACreatorCharacter::Confirm(int32 mapToLoadToNext)
{

	//Get world
	UWorld* World = GetWorld();
	if (nullptr != World)
	{
		//Get Game instance = GI
		UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
		if (nullptr != GI)
		{
			GI->SavePlayerWardrobeData(this);
			GI->LoadMapHUB();
		}
	}
}

void ACreatorCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Setting up Widget

	APlayerController* CCcontroller = Cast<APlayerController>(GetController());

	if (IsValid(CCcontroller))
	{
		WC_Cosmetic = CreateWidget<UCharacterCreatorWidget>(CCcontroller, CosmeticWidget);
		if (IsValid(WC_Cosmetic))
		{
			WC_Cosmetic->AddToViewport(2);
			WC_Cosmetic->LFaceBTN->OnClicked.AddDynamic(this, &ACreatorCharacter::IncrementEmoDown);
			WC_Cosmetic->RFaceBTN->OnClicked.AddDynamic(this, &ACreatorCharacter::IncrementEmoUp);
			WC_Cosmetic->LBodyBTN->OnClicked.AddDynamic(this, &ACreatorCharacter::IncrementSkinDown);
			WC_Cosmetic->RBodyBTN->OnClicked.AddDynamic(this, &ACreatorCharacter::IncrementSkinUp);

			WC_Cosmetic->Start->OnPassNumber.AddDynamic(this, &ACreatorCharacter::Confirm);

			//LOAD EXISTING IF HAS
			//Get world
			UWorld* World = GetWorld();
			if (nullptr != World)
			{
				//Get Game instance = GI
				UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
				if (nullptr != GI)
				{
					if (GI->savingData.saveFilesExist)
					{
						if (GI->savingData.playerSavedata != nullptr)
						{
							SkinIndex = GI->savingData.playerSavedata->playerSaveInfo.skinIndex;
							EmoIndex = GI->savingData.playerSavedata->playerSaveInfo.emotionIndex;
							ApplySkinAndEmo(SkinIndex, EmoIndex);

						}

					}
				}
			}


			WC_Cosmetic->ShowShop();
		}
	}


}


#pragma region Skin_Increments

void ACreatorCharacter::IncrementSkinUp()
{
	if (SkinIndex >= (PlayerSkins.Num() - 1))
	{
		SkinIndex = 0;
	}
	else
	{
		SkinIndex++;
	}

	if (!ApplySkin(SkinIndex))
	{
		ApplySkin(0);
	}

}

void ACreatorCharacter::IncrementSkinDown()
{

	if (SkinIndex <= 0)
	{
		SkinIndex = (PlayerSkins.Num() - 1);
	}
	else
	{
		SkinIndex--;
	}

	if (!ApplySkin(SkinIndex))
	{
		ApplySkin((PlayerSkins.Num() - 1));
	}

}

void ACreatorCharacter::IncrementEmoUp()
{

	if (EmoIndex >= (PlayerEmos.Num() - 1))
	{
		EmoIndex = 0;
	}
	else
	{
		EmoIndex++;
	}

	if (!ApplyEmo(EmoIndex))
	{
		ApplyEmo(0);
	}

}

void ACreatorCharacter::IncrementEmoDown()
{

	if (EmoIndex <= 0)
	{
		EmoIndex = (PlayerEmos.Num() - 1);
	}
	else
	{
		EmoIndex--;
	}

	if (!ApplyEmo(EmoIndex))
	{
		ApplyEmo((PlayerEmos.Num() - 1));
	}

}

#pragma endregion
