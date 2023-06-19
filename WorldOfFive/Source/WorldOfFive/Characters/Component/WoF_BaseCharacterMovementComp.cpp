// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Component/WoF_BaseCharacterMovementComp.h"

float UWoF_BaseCharacterMovementComp::GetMaxSpeed() const
{
	float Result = Super::GetMaxSpeed();
	if (bIsSprinting)
	{
		Result = SprintSpeed;
	}
	return Result;
}

void UWoF_BaseCharacterMovementComp::StartSprint()
{
	bIsSprinting = true;
	bForceMaxAccel = 1;
}

void UWoF_BaseCharacterMovementComp::StopSprint()
{
	bIsSprinting = false;
	bForceMaxAccel = 0;
}
