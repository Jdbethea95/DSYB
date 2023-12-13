// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/DebugAddItemButtonWidget.h"

//UI BP includes
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
// text
#include "Components/TextBlock.h"
#include "Fonts/SlateFontInfo.h"
//Audio
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
UDebugAddItemButtonWidget::UDebugAddItemButtonWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TSubclassOf<UUserWidget>WidgetType = UDebugAddItemButtonWidget::StaticClass();

}

void  UDebugAddItemButtonWidget::UDebugAddItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	IncrementAmount = 1;
}

int32 UDebugAddItemButtonWidget::IncrementItem(int32 amount, bool add = true)
{
	if (add)
	{
		return amount += IncrementAmount;
	}

		return amount -= IncrementAmount;
	
	
}
void UDebugAddItemButtonWidget::SetNameText(FText name)
{
	if (nameTextBlock != nullptr)
	{
	nameTextBlock->SetText(name);
	}
	
}
void UDebugAddItemButtonWidget::UpdateFontSize()
{
	if (nameTextBlock != nullptr && fontSize > 0)
	{
		// need slate module in project .cs
		FSlateFontInfo fontInfo = nameTextBlock->GetFont();
		fontInfo.Size = fontSize;
		nameTextBlock->SetFont(fontInfo);
	}
}
#if WITH_EDITOR

void UDebugAddItemButtonWidget::OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)
{
	SetNameText(nameOfItem);
	UpdateFontSize();
	
}


#endif