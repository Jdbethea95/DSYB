// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BeanItem.h"

ABeanItem::ABeanItem()
{
	type = EItemType::IT_Bean;
	itemID = FName("BN001");
}

void ABeanItem::Use()
{
}
