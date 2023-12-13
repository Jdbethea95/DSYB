// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonwWithTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UButtonwWithTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UButtonwWithTextWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
		class UButton* buttonWTXT;

#pragma region Audio 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|SFX")
		class USoundBase* ClickSFX;
	UFUNCTION(BlueprintCallable)
		void ClickSound();



#pragma endregion 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Button")
		FText buttonText = FText::FromString(TEXT("Temp Text"));

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Button")
		float fontSize;

		UFUNCTION(BlueprintCallable, Category = "UI|Button")
		void UpdateFontSize();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UI|Button")
		class UTextBlock* buttonTextBlock;

	UFUNCTION(BlueprintCallable, Category = "UI|Tab")
	void SetButtonText(FString txt);

	UFUNCTION(BlueprintCallable, Category = "UI|Button")
	UButton* GetButton();
protected:

#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
#endif
};
