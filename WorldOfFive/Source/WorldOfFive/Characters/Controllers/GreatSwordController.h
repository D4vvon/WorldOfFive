// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GreatSwordController.generated.h"

/**
 * 
 */
UCLASS()
class WORLDOFFIVE_API AGreatSwordController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<class UPlayerHUDWidget> GreatSwordHUDWidgetClass;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void Jump();

	void ChangeCrouchState();
	void Roll();

	void Strafe();

	void EquipMeleeWeapon();
	void AttackWeaponMelee();
	void AttackBodyMelee();
	void Blocking();

	void CastSkillBuff();
	void CastSkillAttack();

	void CreateAndInitializeWidgets();
	class UPlayerHUDWidget* GreatSwordHUDWidget = nullptr;

	TSoftObjectPtr<class AGreatSwordCharacter> PlayerCharacter;
};
