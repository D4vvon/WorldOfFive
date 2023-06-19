// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WoF_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WORLDOFFIVE_API AWoF_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<class UPlayerHUDWidget> PlayerHUDWidgetClass;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void Jump();

	void ChangeCrouchState();
	void Roll();

	void Strafe();
	void StartSprint();
	void StopSprint();

	void Fire();

	void CreateAndInitializeWidgets();
	class UPlayerHUDWidget* PlayerHUDWidget = nullptr;

	TSoftObjectPtr<class AWoF_BaseCharacter> BaseCharacter;
};
