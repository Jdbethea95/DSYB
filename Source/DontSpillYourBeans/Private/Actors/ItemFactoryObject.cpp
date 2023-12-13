// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/ItemFactoryObject.h"


UItemFactoryObject::UItemFactoryObject()
{
	//The path to the data base table	
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataBase(TEXT("DataTable'/Game/Core/Databases/Item_DataTable.Item_DataTable'"));

	//Make database table 
	ItemTable = ItemDataBase.Object;
}

void UItemFactoryObject::ItemDatabaseCreation()
{
	//Is item table null?
	if (!IsValid(ItemTable))
	{
		UE_LOG(LogTemp, Warning, TEXT(" Table was Null!"));
	}
	else
	{
		//Names in the table
		TArray<FName> rowNames = ItemTable->GetRowNames();

		//print name count
		UE_LOG(LogTemp, Warning, TEXT("Item Database name Count: %d"), rowNames.Num());
		
		//Making items
		for (size_t i = 0; i < rowNames.Num(); i++)
		{
			//Make item out of row information.
			FItem* item = ItemTable->FindRow<FItem>(rowNames[i], TEXT(""));

			//Is item valid?
			if (item == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT(" database item was Null!"));
				continue;
			}

			//Sort item based on type
			switch (item->type)
			{
			case EItemType::IT_Bean:
				CollectablesList.Add(item->ID,
					CreateBeanItem(
						item->type,
						item->ID,
						item->Name,
						item->sprite));
				break;
			case EItemType::IT_CONSUMABLE:
				ConsumablesList.Add(item->ID,
					CreateConsumableItem(
						item->type,
						item->ID,
						item->Name,
						item->sprite,
						item->effectDuration));
				break;
			default:
				break;
			}
		}

		//UE_LOG(LogTemp, Warning, TEXT(" Item Bank Count: %d"), ItemList.Num());
	}
}

AConsumableItem* UItemFactoryObject::GetConsumableItem(FName itemID)
{
	if (ConsumablesList.IsEmpty() || !ConsumablesList.Contains(itemID))
	{
		UE_LOG(LogTemp, Error, TEXT("Consumable List ID NOT FOUND"));
		return nullptr;
	}
	
	return ConsumablesList[itemID];
}

ABeanItem* UItemFactoryObject::GetCollectableItem(FName itemID)
{
	if (CollectablesList.IsEmpty() || !CollectablesList.Contains(itemID))
	{
		UE_LOG(LogTemp, Error, TEXT("Collectables List ID NOT FOUND"));
		return nullptr;
	}

	return CollectablesList[itemID];
}

//ABaseItem* UItemFactoryObject::GetItemFromDatabase(FName ID)
//{
//	if (ItemList.Contains(ID))
//		return ItemList[ID];
//	else
//		return ItemList["KY001"];
//}
//
//ABaseItem* UItemFactoryObject::CopyItem(ABaseItem* item)
//{
//	//Item Pointers
//	ABeanItem* beanCopy = nullptr; ABeanItem* beanOld = nullptr;
//	AConsumableItem* conCopy = nullptr; AConsumableItem* conOld = nullptr;
//	ABaseItem* returnItem = nullptr;
//	//UE_LOG(LogTemp, Warning, TEXT(" COPY_TOP"));
//
//	//What type is being copied?
//	switch (ItemList[item->itemID]->type)
//	{
//	case EItemType::IT_CONSUMABLE:
//
//		conCopy = NewObject<AConsumableItem>();
//		//Fill conOld with information from item to be copied.
//		conOld = Cast<AConsumableItem>(item);
//
//		//Set Values
//		conCopy->type           = conOld->type;
//		conCopy->itemID         = conOld->itemID;
//		conCopy->itemName       = conOld->itemName;
//		conCopy->sprite         = conOld->sprite;
//		conCopy->effectDuration = conOld->effectDuration;
//
//		returnItem = Cast<ABaseItem>(conCopy);
//
//		return returnItem;
//	case EItemType::IT_Bean:
//
//		beanCopy = NewObject<ABeanItem>();
//		//Fill beanOld with information from item to be copied.
//		beanOld = Cast<ABeanItem>(item);
//
//		//Set Values
//		beanCopy->type     = beanOld->type;
//		beanCopy->itemID   = beanOld->itemID;
//		beanCopy->itemName = beanOld->itemName;
//		beanCopy->sprite   = beanOld->sprite;
//		
//		returnItem = Cast<ABaseItem>(beanCopy);
//
//		return returnItem;
//	case EItemType::IT_KEY:
//		break;
//	default:
//		break;
//	}
//
//	//UE_LOG(LogTemp, Warning, TEXT(" COPY_END"));
//	return nullptr;
//}

//ABaseItem* UItemFactoryObject::CopyItem(FName itemID)
//{
//
//	ABaseItem* copyMe = GetItemFromDatabase(itemID);
//
//	//Item Pointers
//	ABeanItem* beanCopy = nullptr; ABeanItem* beanOld = nullptr;
//	AConsumableItem* conCopy = nullptr; AConsumableItem* conOld = nullptr;
//	ABaseItem* returnItem = nullptr;
//	//UE_LOG(LogTemp, Warning, TEXT(" COPY_TOP"));
//
//	//What type is being copied?
//	switch (ItemList[itemID]->type)
//	{
//	case EItemType::IT_CONSUMABLE:
//
//		conCopy = NewObject<AConsumableItem>();
//		//Fill conOld with information from item to be copied.
//		conOld = Cast<AConsumableItem>(copyMe);
//
//		//Set Values
//		conCopy->type = conOld->type;
//		conCopy->itemID = conOld->itemID;
//		conCopy->itemName = conOld->itemName;
//		conCopy->sprite = conOld->sprite;
//		conCopy->effectDuration = conOld->effectDuration;
//
//		/*returnItem = Cast<ABaseItem>(conCopy);*/
//
//		return conCopy;
//	case EItemType::IT_Bean:
//
//		beanCopy = NewObject<ABeanItem>();
//		//Fill beanOld with information from item to be copied.
//		beanOld = Cast<ABeanItem>(copyMe);
//
//		//Set Values
//		beanCopy->type = beanOld->type;
//		beanCopy->itemID = beanOld->itemID;
//		beanCopy->itemName = beanOld->itemName;
//		beanCopy->sprite = beanOld->sprite;
//
//		/*returnItem = Cast<ABaseItem>(beanCopy);*/
//
//		return beanCopy;
//	case EItemType::IT_KEY:
//		break;
//	default:
//		break;
//	}
//
//	//UE_LOG(LogTemp, Warning, TEXT(" COPY_END"));
//	return nullptr;
//}

ABeanItem* UItemFactoryObject::CreateBeanItem(TEnumAsByte<EItemType> type, FName itemID, FText itemName, class UTexture2D* sprite)
{
	ABeanItem* newItem = NewObject<ABeanItem>();
	newItem->type = type;
	newItem->itemID = itemID;
	newItem->itemName = itemName;
	newItem->sprite = sprite;

	return newItem;
}

AConsumableItem* UItemFactoryObject::CreateConsumableItem(TEnumAsByte<EItemType> type, FName itemID, FText itemName, UTexture2D* sprite, float effectDuration)
{
	AConsumableItem* newItem = NewObject<AConsumableItem>();
	newItem->type = type;
	newItem->itemID = itemID;
	newItem->itemName = itemName;
	newItem->sprite = sprite;
	newItem->effectDuration = effectDuration;

	return newItem;
}

