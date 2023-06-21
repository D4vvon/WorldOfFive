// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WoF_BaseCharacter.generated.h"

class UWoF_BaseCharacterMovementComp;
class UCharacterAttributesComponent;
class UCharacterEquipmentComponent;
class UAnimMontage;
UCLASS(Abstract, NotBlueprintable)
class WORLDOFFIVE_API AWoF_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWoF_BaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void MoveForward(float Value) {};
	virtual void MoveRight(float Value) {};
	virtual void Turn(float Value) {};
	virtual void LookUp(float Value) {};

	virtual void ChangeCrouchState();
	virtual void SetCrouching();
	virtual void SetUnCrouching();
	virtual void EndRoll();
	virtual void Roll();

	virtual void StartSprint();
	virtual void StopSprint();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE UWoF_BaseCharacterMovementComp* GetBaseCharacterMovementComponent() { return WoF_BaseCharacterMovementComponent; }

	UCharacterAttributesComponent* GetCharacterAttributesComponent() const;
	UCharacterEquipmentComponent* GetCharacterEquipmentComponent() const;

	virtual void Falling() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void NotifyJumpApex() override;

	void EquipFirstItem();
	void EquipSecondItem();

	void StartFire();
	void StopFire();

	void SetNextSkill();
	void SetPreviousSkill();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Movement")
	float SprintSpeed = 1200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Movement")
	bool bIsCanSprint = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCharacterAttributesComponent* CharacterAttributesComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCharacterEquipmentComponent* CharacterEquipmentComponent;

	virtual void OnDeath();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Animations")
	UAnimMontage* OnDeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Animations")
	UAnimMontage* RollAnimMontage;

	virtual bool CanSprint();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Attributes")
	class UCurveFloat* FallDamageCurve;

	UWoF_BaseCharacterMovementComp* WoF_BaseCharacterMovementComponent;
private:

	void TryChangeSprintState();
	bool bIsSprintRequested = false;

	void EnableRagdoll();
	FTimerHandle DeathMontageTimer;

	FTimerHandle RollMontageTimer;

	FVector CurrentFallApex;
};
