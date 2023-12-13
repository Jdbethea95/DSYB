// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/InventoryPlayer.h"
#include "Interface/BeanCountUserWidget.h"
#include "Interface/SaucePacketRadialMenuWidget.h"
#include "Interface/HealthEffectWidget.h"
#include "Interface/PlayerPromptWidget.h"
#include "Interface/QuestLogWidget.h"
#include "Actors/ItemFactoryObject.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
//For Saving 
#include "Utility/MyGameInstance.h"
AInventoryPlayer::AInventoryPlayer()
{
    isBeanCountShowing = false;
    isQuestLogMenuShowing = false;
    PacketCapacity = 1;

    //Component Attachment
    QuestComponent = CreateDefaultSubobject<UPlayerQuestComponent>(TEXT("QuestComponent"));
}

//Whenever a scene starts
void AInventoryPlayer::BeginPlay()
{
    Super::BeginPlay();

    //Copy over the class
    ItemFactory = subItemFactory.GetDefaultObject();
    ItemFactory->ItemDatabaseCreation();

    //Stuff...dont go looking for it
    InitializeFunctionPointers();

    // Zeros will be replaced with saved values
    currBeanCount = 0;
    currMagicBeanCount = 0;
    // Packet Counts
    currRedPacketCount = 0;
    currGreenPacketCount = 0;
    currYellowPacketCount = 0;
    currGreyPacketCount = 0;

    PlayerController = Cast<APlayerController>(GetController());

    if (!IsValid(PlayerController))
    {
        return;
    }

#pragma region Widget Creation

    WC_BeanCount = CreateWidget<UBeanCountUserWidget>(PlayerController, BeanCountBase);
    WC_RadialMenu = CreateWidget<USaucePacketRadialMenuWidget>(PlayerController, RadialMenuBase);
    WC_HealthEffect = CreateWidget<UHealthEffectWidget>(PlayerController, HealthEffectBase);
    WC_PlayerPrompt = CreateWidget<UPlayerPromptWidget>(PlayerController, PlayerPromptBase);
    WC_QuestLog = CreateWidget<UQuestLogWidget>(PlayerController, QuestLogBase);

#pragma endregion

#pragma region Widget Checks

    if (!IsValid(WC_BeanCount))
    {
        //UE_LOG(LogTemp, Error, TEXT("Bean Count Null"));
        return;
    }
    else
    {
        WC_BeanCount->AddToViewport(0);
    }

    if (!IsValid(WC_RadialMenu))
    {
        //UE_LOG(LogTemp, Error, TEXT("Radial Menu Null"));
        return;
    }
    else
    {
        if (IsValid(WC_RadialMenu->TopLeftBtn))
            WC_RadialMenu->TopLeftBtn->OnClicked.AddUniqueDynamic(this, &AInventoryPlayer::ActivateGreenPacket);
        else
        {
            //UE_LOG(LogTemp, Error, TEXT("TopLeftBtn Null"));
            return;
        }

        if (IsValid(WC_RadialMenu->TopBtn))
            WC_RadialMenu->TopBtn->OnClicked.AddUniqueDynamic(this, &AInventoryPlayer::ActivateYellowPacket);
        else
        {
            //UE_LOG(LogTemp, Error, TEXT("TopBtn Null"));
            return;
        }

        if (IsValid(WC_RadialMenu->TopRightBtn))
            WC_RadialMenu->TopRightBtn->OnClicked.AddUniqueDynamic(this, &AInventoryPlayer::ActivateRedPacket);
        else
        {
            //UE_LOG(LogTemp, Error, TEXT("TopRightBtn Null"));
            return;
        }

        if (IsValid(WC_RadialMenu->RightBtn))
            WC_RadialMenu->RightBtn->OnClicked.AddUniqueDynamic(this, &AInventoryPlayer::ActivateGreyPacket);
        else
        {
            //UE_LOG(LogTemp, Error, TEXT("RightBtn Null"));
            return;
        }
    }

    if (!IsValid(WC_HealthEffect))
    {
        //UE_LOG(LogTemp, Error, TEXT("Health/Status Effect Element Null"));
        return;
    }
    else
    {
        WC_HealthEffect->Initialize();
        
        HandleHealthBar();

        WC_HealthEffect->AddToViewport(0);

        WC_HealthEffect->Destruct();
    }

    if (!IsValid(WC_PlayerPrompt))
    {
        //UE_LOG(LogTemp, Error, TEXT("Bean Count Null"));
        return;
    }
    else
    {
        
    }

    if (!IsValid(WC_QuestLog))
    {
        UE_LOG(LogTemp, Error, TEXT("Quest Log Null"));
        return;
    }
    else
    {

    }

#pragma endregion

#pragma region Packet Count Check For Opactiy

    if (currRedPacketCount == 0)
        WC_RadialMenu->TopRightImg->SetOpacity(0.3f);
    else
        WC_RadialMenu->TopRightImg->SetOpacity(1.0f);

    if (currGreenPacketCount == 0)
        WC_RadialMenu->TopLeftImg->SetOpacity(0.3f);
    else
        WC_RadialMenu->TopLeftImg->SetOpacity(1.0f);

    if (currYellowPacketCount == 0)
        WC_RadialMenu->TopImg->SetOpacity(0.3f);
    else
        WC_RadialMenu->TopImg->SetOpacity(1.0f);

    if (currGreyPacketCount == 0)
        WC_RadialMenu->RightImg->SetOpacity(0.3f);
    else
        WC_RadialMenu->RightImg->SetOpacity(1.0f);

#pragma endregion

    //Get world
    UWorld* World = GetWorld();
    if (nullptr != World)
    {
        //Get Game instance = GI
        UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
        if (nullptr != GI)
        {
            GamesInstance = GI;
            LoadPlayerData();


        }
    }
}

void AInventoryPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EIComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    if (IsValid(EIComponent))
    {
         //Thats it
         EIComponent->BindAction(InventoryInputAction, ETriggerEvent::Started, this, &AInventoryPlayer::ToggleRadialMenu);

         EIComponent->BindAction(QuestLogInputAction, ETriggerEvent::Started, this, &AInventoryPlayer::ToggleQuestLogMenu);
    }
}

void AInventoryPlayer::ToggleBeanCount()
{
    if (this->GetController() == nullptr)
    {
        return;
    }

    if (WC_BeanCount == nullptr)
    {
    
        return;
    }

    if (!isBeanCountShowing)
    {
        WC_BeanCount->Show();

        isBeanCountShowing = true;
    }
    else
    {
        WC_BeanCount->Hide();

        isBeanCountShowing = false;
    }
}

void AInventoryPlayer::ToggleRadialMenu()
{
    if (this->GetController() == nullptr)
    {
        return;
    }

    if (WC_RadialMenu == nullptr)
    {
        return;
    }

    if (!isRadialMenuShowing)
    {
        WC_RadialMenu->Show();
        isRadialMenuShowing = true;
    }
    else
    {
        WC_RadialMenu->Hide();
        isRadialMenuShowing = false;
    }
}

void AInventoryPlayer::ToggleQuestLogMenu()
{
    

    if (this->GetController() == nullptr || WC_QuestLog == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ToggleQuestLogMenu Null or Controller Null"));
        return;
    }

    if (!isQuestLogMenuShowing)
    {
        WC_QuestLog->Show();
        isQuestLogMenuShowing = true;
    }
    else
    {
        WC_QuestLog->Hide();
        isQuestLogMenuShowing = false;
    }
}

void AInventoryPlayer::ActivateRedPacket()
{
    if (currRedPacketCount > 0 && !WC_HealthEffect->bIsFlashing)
    {
        AConsumableItem* RedPacket = ItemFactory->GetConsumableItem("PA001");
        //Status effect color and duration adjusted to packet being used
        WC_HealthEffect->StartStatusEffect(RedTint, WC_HealthEffect->GetTotalDuration(RedPacket->effectDuration));
        RemoveRedPacketItem();
        //BasePlayer function call to sync timers
        ActivatePacket(2, WC_HealthEffect->GetTotalDuration(RedPacket->effectDuration));
    }
}

void AInventoryPlayer::ActivateGreenPacket()
{
    if (currGreenPacketCount > 0 && !WC_HealthEffect->bIsFlashing)
    {
        AConsumableItem* GreenPacket = ItemFactory->GetConsumableItem("PA002");
        //Status effect color and duration adjusted to packet being used
        WC_HealthEffect->StartStatusEffect(GreenTint, GreenPacket->effectDuration);
        RemoveGreenPacketItem();
        //BasePlayer function call to sync timers
        ActivatePacket(0, GreenPacket->effectDuration);
        HandleHealthBar();
    }
}

void AInventoryPlayer::ActivateGreyPacket()
{
    if (currGreyPacketCount > 0 && !WC_HealthEffect->bIsFlashing)
    {
        AConsumableItem* GreyPacket = ItemFactory->GetConsumableItem("PA003");
        //Status effect color and duration adjusted to packet being used
        WC_HealthEffect->StartStatusEffect(GreyTint, WC_HealthEffect->GetTotalDuration(GreyPacket->effectDuration));
        RemoveGreyPacketItem();
        //BasePlayer function call to sync timers
        ActivatePacket(3, WC_HealthEffect->GetTotalDuration(GreyPacket->effectDuration));
    }
}

void AInventoryPlayer::ActivateYellowPacket()
{
    if (currYellowPacketCount > 0 && !WC_HealthEffect->bIsFlashing)
    {
        AConsumableItem* YellowPacket = ItemFactory->GetConsumableItem("PA004");
        //Status effect color and duration adjusted to packet being used
        WC_HealthEffect->StartStatusEffect(OrangeTint, WC_HealthEffect->GetTotalDuration(YellowPacket->effectDuration));
        RemoveYellowPacketItem();
        //BasePlayer function call to sync timers
        ActivatePacket(1, WC_HealthEffect->GetTotalDuration(YellowPacket->effectDuration));
    }
}

bool AInventoryPlayer::AddItem(FName itemID, int count)
{
    return AddFunctionsMap.ExecuteBoolIntFunction(itemID, count);
}

bool AInventoryPlayer::AddBeanItem(int count)
{
    WC_BeanCount->Text_BeanCount->GetText().AsNumber(currBeanCount);

    if ((currBeanCount + count) >= 0)
        currBeanCount += count;
    else
        currBeanCount = 0;

    WC_BeanCount->Text_BeanCount->SetText(FText::FromString(FString::FromInt(currBeanCount)));

    return true;
}

bool AInventoryPlayer::AddMagicBeanItem(int count)
{
    WC_BeanCount->Text_MagicBeanCount->GetText().AsNumber(currMagicBeanCount);
    currMagicBeanCount += count;
    WC_BeanCount->Text_MagicBeanCount->SetText(FText::FromString(FString::FromInt(currMagicBeanCount)));

    return true;
}

bool AInventoryPlayer::AddKeyItem(int count)
{
    return false;
}

bool AInventoryPlayer::AddConsumableItem(int count)
{
    return false;
}

bool AInventoryPlayer::AddRedPacketItem(int count)
{
    if (currRedPacketCount == 0)
    {
        WC_RadialMenu->TopRightImg->SetOpacity(1.0f);
    }

    if (currRedPacketCount < 100)
    {
        WC_RadialMenu->TopRightCount->GetText().AsNumber(currRedPacketCount);
        currRedPacketCount += count;
        WC_RadialMenu->TopRightCount->SetText(FText::FromString(FString::FromInt(currRedPacketCount)));
        return true;
    }
    else
    {
        //Create new widget to display max packet count reached
        return true;
    }
}

bool AInventoryPlayer::AddGreenPacketItem(int count)
{
    if (currGreenPacketCount == 0)
        WC_RadialMenu->TopLeftImg->SetOpacity(1.0f);

    if (currGreenPacketCount < 100)
    {
        WC_RadialMenu->TopLeftCount->GetText().AsNumber(currGreenPacketCount);
        currGreenPacketCount += count;
        WC_RadialMenu->TopLeftCount->SetText(FText::FromString(FString::FromInt(currGreenPacketCount)));
        return true;
    }
    else
    {
        //Create new widget to display max packet count reached
        return true;
    }
}

bool AInventoryPlayer::AddYellowPacketItem(int count)
{
    if (currYellowPacketCount == 0)
        WC_RadialMenu->TopImg->SetOpacity(1.0f);

    if (currYellowPacketCount < 100)
    {
        WC_RadialMenu->TopCount->GetText().AsNumber(currYellowPacketCount);
        currYellowPacketCount += count;
        WC_RadialMenu->TopCount->SetText(FText::FromString(FString::FromInt(currYellowPacketCount)));
        return true;
    }
    else
    {
        //Create new widget to display max packet count reached
        return true;
    }
}

bool AInventoryPlayer::AddGreyPacketItem(int count)
{
    if (currGreyPacketCount == 0)
        WC_RadialMenu->RightImg->SetOpacity(1.0f);

    if (currGreyPacketCount < 100)
    {
        WC_RadialMenu->RightCount->GetText().AsNumber(currGreyPacketCount);
        currGreyPacketCount += count;
        WC_RadialMenu->RightCount->SetText(FText::FromString(FString::FromInt(currGreyPacketCount)));
        return true;
    }
    else
    {
        //Create new widget to display max packet count reached
        return true;
    }
}

bool AInventoryPlayer::RemoveRedPacketItem()
{
    if (currRedPacketCount == 0)
    {
        //could use return types enum to print specific message to screen for player
        return false;
    }

    if (currRedPacketCount == 1)
        WC_RadialMenu->TopRightImg->SetOpacity(0.3f);

    WC_RadialMenu->TopRightCount->GetText().AsNumber(currRedPacketCount);
    currRedPacketCount -= 1;
    WC_RadialMenu->TopRightCount->SetText(FText::FromString(FString::FromInt(currRedPacketCount)));

    return true;
}

bool AInventoryPlayer::RemoveGreenPacketItem()
{
    if (currGreenPacketCount == 0)
    {
        //could use return types enum to print specific message to screen for player
        return false;
    }

    if (currGreenPacketCount == 1)
        WC_RadialMenu->TopLeftImg->SetOpacity(0.3f);

    WC_RadialMenu->TopLeftCount->GetText().AsNumber(currGreenPacketCount);
    currGreenPacketCount -= 1;
    WC_RadialMenu->TopLeftCount->SetText(FText::FromString(FString::FromInt(currGreenPacketCount)));

    return true;
}

bool AInventoryPlayer::RemoveYellowPacketItem()
{
    if (currYellowPacketCount == 0)
    {
        //could use return types enum to print specific message to screen for player
        return false;
    }

    if (currYellowPacketCount == 1)
        WC_RadialMenu->TopImg->SetOpacity(0.3f);

    WC_RadialMenu->TopCount->GetText().AsNumber(currYellowPacketCount);
    currYellowPacketCount -= 1;
    WC_RadialMenu->TopCount->SetText(FText::FromString(FString::FromInt(currYellowPacketCount)));

    return true;
}

bool AInventoryPlayer::RemoveGreyPacketItem()
{
    if (currGreyPacketCount == 0)
    {
        //could use return types enum to print specific message to screen for player
        return false;
    }

    if (currGreyPacketCount == 1)
        WC_RadialMenu->RightImg->SetOpacity(0.3f);

    WC_RadialMenu->RightCount->GetText().AsNumber(currGreyPacketCount);
    currGreyPacketCount -= 1;
    WC_RadialMenu->RightCount->SetText(FText::FromString(FString::FromInt(currGreyPacketCount)));

    return true;
}

#pragma region BaseCharacter Overrides

void AInventoryPlayer::SetPlayerPauseState(bool condition)
{

}

void AInventoryPlayer::TogglePlayerPauseState()
{

}

void AInventoryPlayer::PlayerReset()
{
    Super::PlayerReset();
    HandleHealthBar();
}

bool AInventoryPlayer::ModifyHealth(float amount)
{
    Super::ModifyHealth(amount);

    HandleHealthBar();

    return true;
}

void AInventoryPlayer::OnModifyStats()
{
    Super::OnModifyStats();
    UE_LOG(LogTemp, Warning, TEXT("Modify->Curr: %f | max: %f "), PlayerHealth, PlayerMaxHealth);
    WC_HealthEffect->appliedDuration = PassiveStatActor->ApplyPacketDurationPassive(WC_HealthEffect->appliedDuration);
    //New passive level is applied to the player stats being used.
    PacketCapacity = PassiveStatActor->ApplyPacketCapacityPassive(PacketCapacity);
}

void AInventoryPlayer::PurchaseDuration()
{
    if (currBeanCount >= PassiveStatActor->DurationCost)
    {
        //updating UI
        AddBeanItem(-PassiveStatActor->DurationCost);
        Super::PurchaseDuration();
    }
}

void AInventoryPlayer::PurchaseCapacity()
{
    if (currBeanCount >= PassiveStatActor->CapacityCost)
    {
        //updating UI
        AddBeanItem(-PassiveStatActor->CapacityCost);
        Super::PurchaseCapacity();
    }
}

void AInventoryPlayer::PurchaseHealth()
{
    if (currBeanCount >= PassiveStatActor->HealthCost)
    {
        //updating UI
        AddBeanItem(-PassiveStatActor->HealthCost);
        Super::PurchaseHealth();
    }
}

void AInventoryPlayer::PurchaseDoubleJump()
{
    if (currBeanCount >= PassiveStatActor->JumpCost)
    {
        //updating UI
        AddBeanItem(-PassiveStatActor->JumpCost);
        Super::PurchaseDoubleJump();
    }
}

#pragma endregion


 void AInventoryPlayer::HandleHealthBar()
 {
     //temp variables
     float currHealth = PlayerHealth;
     float maxHealth = PlayerMaxHealth;

     //Color blending
     float ColorBlendFactor = 0.0f;
     FLinearColor newColor = FLinearColor(0.0f, 0.0f, 0.0f, 2.0f);

     WC_HealthEffect->ProgressBar_HP->SetPercent(currHealth / maxHealth);

     //Health = 10 to 20
     //color should change from green to yellow
     if (WC_HealthEffect->ProgressBar_HP->GetPercent() >= 0.5f)
     {
         //isolate upper half of bar
         currHealth -= maxHealth * 0.5f;
         ColorBlendFactor = currHealth / (maxHealth * 0.5f);
         //assign color based on lerp
         newColor = FMath::Lerp(YellowTint, GreenTint, ColorBlendFactor);
         WC_HealthEffect->ProgressBar_HP->SetFillColorAndOpacity(newColor);
         WC_HealthEffect->Text_CurrentHealth->SetColorAndOpacity(newColor);
         WC_HealthEffect->Text_CurrentHealth->SetText(FText::FromString(FString::FromInt(currHealth + maxHealth * 0.5f)));
     }
     else if (WC_HealthEffect->ProgressBar_HP->GetPercent() <= 0.5f && 
              WC_HealthEffect->ProgressBar_HP->GetPercent() > 0.0f)
     {
         ColorBlendFactor = currHealth / (maxHealth * 0.5f);
         //assign new color based on lerp
         newColor = FMath::Lerp(RedTint, YellowTint, ColorBlendFactor);
         WC_HealthEffect->ProgressBar_HP->SetFillColorAndOpacity(newColor);
         WC_HealthEffect->Text_CurrentHealth->SetColorAndOpacity(newColor);
         WC_HealthEffect->Text_CurrentHealth->SetText(FText::FromString(FString::FromInt(currHealth)));
     }
     else
     {
         WC_HealthEffect->ProgressBar_HP->SetFillColorAndOpacity(newColor);
         WC_HealthEffect->Text_CurrentHealth->SetText(FText::FromString(FString::FromInt(currHealth)));
     }
 }

 
 float AInventoryPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
 {
     Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

     HandleHealthBar();

     return 0.0f;
 }

 void AInventoryPlayer::SavePlayerData()
 {
     if (GamesInstance != nullptr)
     {
         GamesInstance->SavePlayerData(this);
     }

 }

 void AInventoryPlayer::LoadPlayerData()
 {
     if (GamesInstance != nullptr)
     {
        
   
             GamesInstance->LoadPlayerSaveData(this);
             ApplySkinAndEmo(SkinIndex,EmoIndex);
             UE_LOG(LogTemp, Warning, TEXT("LOAD->Curr: %f | max: %f "), PlayerHealth, PlayerMaxHealth);

             if (PlayerHealth <= 0)
             {
                 PlayerHealth = PlayerMaxHealth;
             }

             PassiveStatActor->UpdateCosts();

             OnModifyStats();
         }






     
 }

 void AInventoryPlayer::InitializeFunctionPointers()
 {
     using namespace std::placeholders;

     AddFunctionsMap.AddBoolIntFunction("BN001", std::bind(&AInventoryPlayer::AddBeanItem, this, _1));
     AddFunctionsMap.AddBoolIntFunction("BN002", std::bind(&AInventoryPlayer::AddMagicBeanItem, this, _1));
     AddFunctionsMap.AddBoolIntFunction("PA001", std::bind(&AInventoryPlayer::AddRedPacketItem, this, _1));
     AddFunctionsMap.AddBoolIntFunction("PA002", std::bind(&AInventoryPlayer::AddGreenPacketItem, this, _1));
     AddFunctionsMap.AddBoolIntFunction("PA003", std::bind(&AInventoryPlayer::AddGreyPacketItem, this, _1));
     AddFunctionsMap.AddBoolIntFunction("PA004", std::bind(&AInventoryPlayer::AddYellowPacketItem, this, _1));
 }
