// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WoF_BaseCharacterMovementComp.generated.h"

/**
 * 
 */
UCLASS()
class WORLDOFFIVE_API UWoF_BaseCharacterMovementComp : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool IsSprinting() { return bIsSprinting; }

	virtual float GetMaxSpeed() const override;

	void StartSprint();
	void StopSprint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Movement | Sprint", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float SprintSpeed = 1200.0f;

private:
	bool bIsSprinting = false;
};
