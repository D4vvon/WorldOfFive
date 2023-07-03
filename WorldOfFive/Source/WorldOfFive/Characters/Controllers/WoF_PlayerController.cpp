// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/WoF_PlayerController.h"
#include "../WoF_BaseCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/ReticleWidget.h"
#include "UI/Widget/PlayerHUDWidget.h"

void AWoF_PlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	BaseCharacter = Cast<AWoF_BaseCharacter>(InPawn);

	//CreateAndInitializeWidgets();
}

void AWoF_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

/*
	InputComponent->BindAxis("MoveForward", this, &AWoF_PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AWoF_PlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &AWoF_PlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &AWoF_PlayerController::LookUp);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::Jump);

	InputComponent->BindAction("Roll", EInputEvent::IE_DoubleClick, this, &AWoF_PlayerController::Roll);
	InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::ChangeCrouchState);

	InputComponent->BindAction("Strafe", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::Strafe);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::StartSprint);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AWoF_PlayerController::StopSprint);

	InputComponent->BindAction("FirstItem", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::EquipFirstItem);
	InputComponent->BindAction("SecondItem", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::EquipSecondItem);
	InputComponent->BindAction("ThirdItem", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::EquipThirdItem);
	InputComponent->BindAction("FourthItem", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::EquipFourthItem);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::StartingFire);
	InputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AWoF_PlayerController::StopFire);
	InputComponent->BindAction("NextSkill", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::SetNextSkill);
	InputComponent->BindAction("PreviousSkill", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::SetPreviousSkill);

	InputComponent->BindAction("EquipMeleeWeapon", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::EquipMeleeWeapon);
	InputComponent->BindAction("AttackWeapon", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::AttackWeaponMelee);
	InputComponent->BindAction("AttackBody", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::AttackBodyMelee);*/
}

void AWoF_PlayerController::MoveForward(float Value)
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->MoveForward(Value);
	}
}

void AWoF_PlayerController::MoveRight(float Value)
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->MoveRight(Value);
	}
}

void AWoF_PlayerController::Turn(float Value)
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->Turn(Value);
	}
}

void AWoF_PlayerController::LookUp(float Value)
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->LookUp(Value);
	}
}

void AWoF_PlayerController::Jump()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->Jump();
	}
}

void AWoF_PlayerController::ChangeCrouchState()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->ChangeCrouchState();
	}
}

/*
void AWoF_PlayerController::Roll()
{
	if (BaseCharacter.IsValid())
	{
		//TODO Roll
		BaseCharacter->Roll();
	}
}

void AWoF_PlayerController::Strafe()
{
	if (BaseCharacter.IsValid())
	{
		//TODO Strafe
	}
}

void AWoF_PlayerController::StartSprint()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->StartSprint();
	}
}

void AWoF_PlayerController::StopSprint()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->StopSprint();
	}
}

void AWoF_PlayerController::EquipFirstItem()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->EquipFirstItem();
	}		
}

void AWoF_PlayerController::EquipSecondItem()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->EquipSecondItem();
	}
}

void AWoF_PlayerController::EquipThirdItem()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->EquipThirdItem();
	}
}

void AWoF_PlayerController::EquipFourthItem()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->EquipFourthItem();
	}
}

void AWoF_PlayerController::StartingFire()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->StartFire();
	}
}

void AWoF_PlayerController::StopFire()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->StopFire();
	}
}

void AWoF_PlayerController::SetNextSkill()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->SetNextSkill();
	}
}

void AWoF_PlayerController::SetPreviousSkill()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->SetPreviousSkill();
	}
}

void AWoF_PlayerController::EquipMeleeWeapon()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->EquipMeleeWeapon();
	}
}

void AWoF_PlayerController::AttackWeaponMelee()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->AttackWeaponMelee();
	}
}

void AWoF_PlayerController::AttackBodyMelee()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->AttackBodyMelee();
	}
}*/

/*
void AWoF_PlayerController::CreateAndInitializeWidgets()
{
	if (!IsValid(PlayerHUDWidget))
	{
		PlayerHUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
		if (IsValid(PlayerHUDWidget))
		{
			PlayerHUDWidget->AddToViewport();
		}
	}

	if (IsValid(PlayerHUDWidget) && BaseCharacter.IsValid())
	{
		UReticleWidget* ReticleWidget = PlayerHUDWidget->GetReticleWidget();
		if (IsValid(ReticleWidget))
		{
			// TODO if character can aiming
		}
	}
}*/
