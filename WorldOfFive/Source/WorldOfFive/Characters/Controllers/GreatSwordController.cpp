// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/GreatSwordController.h"
#include "../GreatSwordCharacter.h"
#include "UI/Widget/PlayerHUDWidget.h"

void AGreatSwordController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	PlayerCharacter = Cast<AGreatSwordCharacter>(InPawn);

	CreateAndInitializeWidgets();
}

void AGreatSwordController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AGreatSwordController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGreatSwordController::MoveRight);
	InputComponent->BindAxis("Turn", this, &AGreatSwordController::Turn);
	InputComponent->BindAxis("LookUp", this, &AGreatSwordController::LookUp);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AGreatSwordController::Jump);
	InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &AGreatSwordController::ChangeCrouchState);
	InputComponent->BindAction("Roll", EInputEvent::IE_DoubleClick, this, &AGreatSwordController::Roll);

	InputComponent->BindAction("EquipMeleeWeapon", EInputEvent::IE_Pressed, this, &AGreatSwordController::EquipMeleeWeapon);
	InputComponent->BindAction("AttackWeapon", EInputEvent::IE_Pressed, this, &AGreatSwordController::AttackWeaponMelee);
	InputComponent->BindAction("AttackBody", EInputEvent::IE_Pressed, this, &AGreatSwordController::AttackBodyMelee);
	InputComponent->BindAction("Blocking", EInputEvent::IE_Pressed, this, &AGreatSwordController::Blocking);

	InputComponent->BindAction("CastSkillBuff", EInputEvent::IE_Pressed, this, &AGreatSwordController::CastSkillBuff);
	InputComponent->BindAction("CastSkillAttack", EInputEvent::IE_Pressed, this, &AGreatSwordController::CastSkillAttack);
}

void AGreatSwordController::MoveForward(float Value)
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->MoveForward(Value);
	}
}

void AGreatSwordController::MoveRight(float Value)
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->MoveRight(Value);
	}
}

void AGreatSwordController::Turn(float Value)
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->Turn(Value);
	}
}

void AGreatSwordController::LookUp(float Value)
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->LookUp(Value);
	}
}

void AGreatSwordController::Jump()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->Jump();
	}
}

void AGreatSwordController::ChangeCrouchState()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->ChangeCrouchState();
	}
}

void AGreatSwordController::Roll()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->Roll();
	}
}

void AGreatSwordController::Strafe()
{
	if (PlayerCharacter.IsValid())
	{
		//PlayerCharacter->
	}
}

void AGreatSwordController::EquipMeleeWeapon()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->EquipMeleeWeapon();
	}
}

void AGreatSwordController::AttackWeaponMelee()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->AttackWeaponMelee();
	}
}

void AGreatSwordController::AttackBodyMelee()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->AttackBodyMelee();
	}
}

void AGreatSwordController::Blocking()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->Blocking();
	}
}

void AGreatSwordController::CastSkillBuff()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->CastSkillBuff();
	}
}

void AGreatSwordController::CastSkillAttack()
{
	if (PlayerCharacter.IsValid())
	{
		PlayerCharacter->CastSkillAttack();
	}
}

void AGreatSwordController::CreateAndInitializeWidgets()
{
	if (!IsValid(GreatSwordHUDWidget))
	{
		GreatSwordHUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), GreatSwordHUDWidgetClass);
		if (IsValid(GreatSwordHUDWidget))
		{
			GreatSwordHUDWidget->AddToViewport();
		}
	}
}
