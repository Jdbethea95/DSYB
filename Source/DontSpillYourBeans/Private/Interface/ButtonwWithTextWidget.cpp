// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/ButtonwWithTextWidget.h"


//UI BP includes
#include "Components/VerticalBox.h"
#include "Components/Button.h"
// text
#include "Components/TextBlock.h"
#include "Fonts/SlateFontInfo.h"
//Audio
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
UButtonwWithTextWidget::UButtonwWithTextWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TSubclassOf<UUserWidget>WidgetType = UButtonwWithTextWidget::StaticClass();

}
void UButtonwWithTextWidget::NativeConstruct()
{
    Super::NativeConstruct();
    buttonWTXT->OnClicked.AddDynamic(this, &UButtonwWithTextWidget::ClickSound);
    if (buttonTextBlock != nullptr)
    {
        buttonTextBlock->SetText(buttonText);
       
        UpdateFontSize();
    }

}
void UButtonwWithTextWidget::ClickSound()
{
    PlaySound(ClickSFX);
}

void UButtonwWithTextWidget::UpdateFontSize()
{

        if (buttonTextBlock != nullptr && fontSize > 0)
        {
            // need slate module in project .cs
            FSlateFontInfo fontInfo =buttonTextBlock->GetFont();
           fontInfo.Size = fontSize;
           buttonTextBlock->SetFont(fontInfo);
        }

}

void UButtonwWithTextWidget::SetButtonText(FString txt)
{
    buttonText = FText::FromString((txt));
    buttonTextBlock->SetText(FText::FromString(txt));

}

UButton* UButtonwWithTextWidget::GetButton()
{
    return buttonWTXT;
}


#if WITH_EDITOR
void UButtonwWithTextWidget::OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)
{
    Super::OnDesignerChanged(EventArgs);
    if (buttonTextBlock !=nullptr )
    {
        if (fontSize == 0)
        {
            FSlateFontInfo fontInfo = buttonTextBlock->GetFont();
            fontSize = fontInfo.Size;
        }
        buttonTextBlock->SetText(buttonText);
       UpdateFontSize();
    }

}
#endif