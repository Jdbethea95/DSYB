// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Pawn/InventoryPlayer.h"
#include "PlayerPromptTrigger.generated.h"

UCLASS()
class DONTSPILLYOURBEANS_API APlayerPromptTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerPromptTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision|Collider")
		class USphereComponent* SphereCollider;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|Editor Only")
		class UStaticMeshComponent* EditorBoxMesh;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prompt")
		FText PromptTxt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Title")
		FText TitleTxt;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool shown;
};
