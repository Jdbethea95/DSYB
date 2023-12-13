// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/TextButtonWithIntWidget.h"
#include "Components/Button.h"


void UTextButtonWithIntWidget::NativeConstruct()
{
    Super::NativeConstruct();
    //on click pass buttons number
    buttonWTXT->OnClicked.AddDynamic(this, &UTextButtonWithIntWidget::PassNumber);


}
void UTextButtonWithIntWidget::PassNumber()
{ 
	OnPassNumber.Broadcast(number);
   
        
}
#if WITH_EDITOR



void UTextButtonWithIntWidget::OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)
{
    Super::OnDesignerChanged(EventArgs);
}

#endif