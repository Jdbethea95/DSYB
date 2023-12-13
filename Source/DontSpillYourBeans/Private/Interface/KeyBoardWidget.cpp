// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/KeyBoardWidget.h"
//---UI
//Buttons
#include "Interface/ButtonwWithTextWidget.h"
#include "Interface/TextButtonWithIntWidget.h"
#include "Interface/ButtonPassStringWidget.h"
#include "Components/Button.h"
// text
#include "Components/TextBlock.h"



void UKeyBoardWidget::NativeConstruct()
{
    //Super::NativeConstruct();
	BindButtons();
}

void UKeyBoardWidget::BindButtons()
{
	buttonEnter->buttonWTXT->OnClicked.AddDynamic(this, &UKeyBoardWidget::Enter);
	buttonDelete->buttonWTXT->OnClicked.AddDynamic(this, &UKeyBoardWidget::Delete);



}

void UKeyBoardWidget::Enter()
{

	OnEnterPressed.Broadcast();
}

void UKeyBoardWidget::Delete()
{

	outputWord = outputWord.LeftChop(1);
	UpdateDisplayText();
	if (outputWord.IsEmpty())
	{
		buttonEnter->buttonWTXT->SetIsEnabled(false);
	}
	else
	{
		buttonEnter->buttonWTXT->SetIsEnabled(true);
	}
}



FString  UKeyBoardWidget::GetOutputWord()
{
	return outputWord;
}

void UKeyBoardWidget::UpdateDisplayText()
{
	outputDisplayText->SetText(FText::FromString(GetOutputWord()));
	buttonEnter->word = outputWord;
}

FString  UKeyBoardWidget::GetLetter(int32 lettersIndex)
{
	if (Letters.IsValidIndex(lettersIndex))
	{
		return Letters[lettersIndex];
	}
	return "FAILED";
}

void UKeyBoardWidget::PressedALetter(int32 lettersIndex)
{
	FString temp = GetLetter(lettersIndex);
	if (temp != "FAILED")
	{
		outputWord.Append(temp);
		UpdateDisplayText();
		if (outputWord.IsEmpty())
		{
			buttonEnter->buttonWTXT->SetIsEnabled(false);
		}
		else
		{
			buttonEnter->buttonWTXT->SetIsEnabled(true);
		}
	}
	
		
}
