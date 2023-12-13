// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ConsumableItem.h"

AConsumableItem::AConsumableItem()
{
	itemID = FName("PA001");
	type = EItemType::IT_CONSUMABLE;
}
