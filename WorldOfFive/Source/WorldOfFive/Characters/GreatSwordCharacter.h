// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WoF_BaseCharacter.h"
#include "GreatSwordCharacter.generated.h"

class UWoF_BaseCharacterMovementComp;
class UGreatSwordAttributesComponent;
class UCharacterEquipmentComponent;
class UAnimMontage;
class USceneComponent;
UCLASS(Blueprintable)
class WORLDOFFIVE_API AGreatSwordCharacter : public AWoF_BaseCharacter
{
	GENERATED_BODY()
	
public:
	AGreatSwordCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	void EndRoll();
	void Roll();

	virtual void Tick(float DeltaSeconds) override;

	void EquipMeleeWeapon();
	void AttackWeaponMelee();
	void AttackBodyMelee();
	virtual void Blocking() override;
	virtual bool GetIsBlocking() override;
	virtual void SetIsBlocking(bool NewIsBlocking) override;

	void CastSkillBuff();
	void CastSkillAttack();
	virtual USceneComponent* GetSkillPointLocation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Animations")
	UAnimMontage* RollAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Components")
	USceneComponent* CharacterSkillPointLocation;


private:
	bool bIsBlocking = false;

	FTimerHandle RollMontageTimer;
};
