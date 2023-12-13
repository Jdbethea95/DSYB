// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/ButtonPassStringWidget.h"

#include "Components/Button.h"


void UButtonPassStringWidget::NativeConstruct()
{
    Super::NativeConstruct();

   buttonWTXT->OnClicked.AddDynamic(this, &UButtonPassStringWidget::PassAWord);
 
}

void UButtonPassStringWidget::PassAWord()
{
    OnPassAWord.Broadcast(word);
}

