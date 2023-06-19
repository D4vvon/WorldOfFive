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

	CreateAndInitializeWidgets();
}

void AWoF_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

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

	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AWoF_PlayerController::Fire);
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

void AWoF_PlayerController::Fire()
{
	if (BaseCharacter.IsValid())
	{
		BaseCharacter->Fire();
	}
}

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
}
