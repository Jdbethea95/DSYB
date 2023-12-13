// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UENUM(BlueprintType)
enum EItemType
{
	IT_Bean       UMETA(DisplayName = "Bean"),
	IT_KEY        UMETA(DisplayName = "KeyItem"),
	IT_CONSUMABLE UMETA(DisplayName = "ConsumableItem"),
	IT_EMPTY      UMETA(DisplayName = "EMPTY")
};

UCLASS()
class DONTSPILLYOURBEANS_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


#pragma region Info

	//ID: Determines which item is present (Bean or Consumable)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Info")
		TEnumAsByte<EItemType> type;

	//TEnumAsByte used to ensure EItemType is used
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Info")
		FName itemID;

	//Name
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Info")
		FText itemName;

	//2DTexture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Display")
		class UTexture2D* sprite;

#pragma endregion

	UFUNCTION()
		virtual void Use();

};
