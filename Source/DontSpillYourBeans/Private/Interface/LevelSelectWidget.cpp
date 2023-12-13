// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/LevelSelectWidget.h"


//Functionality includes
#include "Utility/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

//UI BP includes
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
//UI Widgets coded

ULevelSelectWidget::ULevelSelectWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TSubclassOf<UUserWidget>WidgetType = ULevelSelectWidget::StaticClass();

}

void ULevelSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();
    //Get world
    UWorld* World = GetWorld();
    if (nullptr != World)
    {
        //Get Game instance = GI
        UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
        if (nullptr != GI)
        {
            GamesInstance = GI;
            Super::NativeConstruct();

        }
    }
}

//shows game maps meant to be used in hub cauldron
void ULevelSelectWidget::MakeLevelInfoButtonChildren()
{

}

void ULevelSelectWidget::ClearChildrenFromScrollBox()
{

}
//Displays level buttons with no bean cost and testing maps
void ULevelSelectWidget::MakeDebugChildren()
{

}
