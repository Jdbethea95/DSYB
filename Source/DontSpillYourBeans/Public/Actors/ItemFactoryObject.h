// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Actors/BaseItem.h"
#include "Actors/BeanItem.h"
#include "Actors/ConsumableItem.h"
#include "ItemFactoryObject.generated.h"

USTRUCT(BlueprintType) struct FItem : public FTableRowBase
{
	GENERATED_BODY()

public:

	

	//Bean, Consumable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EItemType> type;

	//Beans, Magic Beans, Packets
	//Beans Normal = BN001, BN002
	//Packets = PA001, PA002, PA003, PA004
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ID;

	//Item specific title
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	//Item Specific Icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* sprite;

	//Consumable Item Info
	//Effect Duration
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float effectDuration;

	FItem()
	{

	}

	FItem& FItem::operator =(const FItem& other)
	{
		ID          = other.ID;
		Name        = other.Name;
		effectDuration = other.effectDuration;
		type		= other.type;
		sprite		= other.sprite;

		return *this;
	}
};
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DONTSPILLYOURBEANS_API UItemFactoryObject : public UObject
{
	GENERATED_BODY()
	
public:

	UItemFactoryObject();

	//Table with item info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
		class UDataTable* ItemTable;

	//List of items
	TMap<FName, AConsumableItem*> ConsumablesList;

	TMap<FName, ABeanItem*> CollectablesList;

	//List of sprites
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprites")
		TArray<UTexture2D*> ItemSprites;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Classes")
		TSubclassOf<class ABeanItem> BeanItemBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Classes")
		TSubclassOf<class AConsumableItem> ConsumableItemBase;*/

	UFUNCTION()
		void ItemDatabaseCreation();

	AConsumableItem* GetConsumableItem(FName itemID);

	ABeanItem* GetCollectableItem(FName itemID);

	//class ABaseItem* GetItemFromDatabase(FName ID);
	//class ABaseItem* CopyItem(ABaseItem* item);
	//class ABaseItem* CopyItem(FName itemID);

private:
	class ABeanItem* CreateBeanItem(TEnumAsByte<EItemType> type, FName itemID, FText itemName, class UTexture2D* sprite);
	class AConsumableItem* CreateConsumableItem(TEnumAsByte<EItemType> type, FName itemID, FText itemName, class UTexture2D* sprite, float effectDuration = 0);

};
