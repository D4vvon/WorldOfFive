// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WoF_BaseCharacter.h"
#include "WizzardCharacter.generated.h"

/**
 * 
 */
UCLASS()
class WORLDOFFIVE_API AWizzardCharacter : public AWoF_BaseCharacter
{
	GENERATED_BODY()
	

public:
	AWizzardCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USpringArmComponent* SpringArmComponent;
};
