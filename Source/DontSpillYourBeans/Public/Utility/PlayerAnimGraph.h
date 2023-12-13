// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimGraph.generated.h"

/**
 * 
 */
UCLASS()
class DONTSPILLYOURBEANS_API UPlayerAnimGraph : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isDeath;

	bool getAttacking();
	void setAttacking(bool Attacking = true);

	UFUNCTION(BlueprintCallable)
		void PlayAttack();

	UFUNCTION(BlueprintCallable)
		void PlayHurt();

	UFUNCTION(BlueprintCallable)
		void PlayDeath();

	bool GetJump();
	void SetJump(bool Jumping = true);

	UFUNCTION(BlueprintCallable)
		void PlayJump();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
		bool isAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
		bool isJumping;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		TArray<UAnimSequence*> Attacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimSequence* Damaged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimSequence* Death;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimSequence* jumpSequence;

};
