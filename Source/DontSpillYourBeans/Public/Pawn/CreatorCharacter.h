// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/BaseCharacter.h"
#include "CreatorCharacter.generated.h"


class UCharacterCreatorWidget;
/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API ACreatorCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	

public:
	ACreatorCharacter();




#pragma region CosmeticComponent


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCharacterCreatorWidget* WC_Cosmetic;

/// <summary>
/// Confirms the settings by saving and loading to the desired map
/// </summary>
		UFUNCTION(BlueprintCallable, Category = "UI|Char Create")
		virtual void Confirm(int32 mapToLoadToNext);
#pragma endregion

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UCharacterCreatorWidget> CosmeticWidget;

	UFUNCTION()
	void IncrementSkinUp();
	UFUNCTION()
	void IncrementSkinDown();
	UFUNCTION()
	void IncrementEmoUp();
	UFUNCTION()
	void IncrementEmoDown();
};
