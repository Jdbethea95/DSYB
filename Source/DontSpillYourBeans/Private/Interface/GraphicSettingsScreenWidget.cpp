// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/GraphicSettingsScreenWidget.h"//UI 
#include "Interface/ButtonwWithTextWidget.h"
#include "Components/Button.h"
//display 
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"

UGraphicSettingsScreenWidget::UGraphicSettingsScreenWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TSubclassOf<UUserWidget>WidgetType = UGraphicSettingsScreenWidget::StaticClass();
}

void UGraphicSettingsScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UGameUserSettings* GS = GEngine->GameUserSettings;
    if (GS)
    {
        GameSettings = GS;
        //bind confirm
        buttonConfirm->buttonWTXT->OnClicked.AddDynamic(this, &UGraphicSettingsScreenWidget::ConfirmSettings);

    }
    buttonConfirm->SetIsEnabled(false);
    //add screen options

    DisplayModeComboBox->AddOption("FULL SCREEN");
    DisplayModeComboBox->AddOption("WINDOWED");
    DisplayModeComboBox->AddOption("WINDOWED FULL SCREEN");
    DisplayModeComboBox->SetSelectedOption("FULL SCREEN");
    DisplayModeComboBox->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsScreenWidget::SetDisplayMode);
}


void UGraphicSettingsScreenWidget::SetDisplayMode(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    if (GameSettings != nullptr)
    {
        if (SelectedItem == "FULL SCREEN")
        {
            GameSettings->SetFullscreenMode(EWindowMode::Fullscreen);
            buttonConfirm->SetIsEnabled(true);
        }
        else if (SelectedItem == "WINDOWED FULL SCREEN")
        {
            GameSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
            buttonConfirm->SetIsEnabled(true);
        }
        else if (SelectedItem == "WINDOWED")
        {
            GameSettings->SetFullscreenMode(EWindowMode::Windowed);
            buttonConfirm->SetIsEnabled(true);
        }
    }

}

void UGraphicSettingsScreenWidget::ConfirmSettings()
{
    if (GameSettings != nullptr)
    {
        GameSettings->ApplySettings(true);
        buttonConfirm->SetIsEnabled(false);
    }
}
