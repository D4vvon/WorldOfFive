// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WizzardCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/WoF_BaseCharacterMovementComp.h"
#include "GameFramework/Character.h"
#include "Component/CharacterAttributesComponent.h"
#include "WorldOfFive_Types.h"
#include "Engine/DamageEvents.h"
#include "Component/CharacterEquipmentComponent.h"
#include "Actors/Equipment/Weapons/RangeWeaponItem.h"

AWizzardCharacter::AWizzardCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = 1;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	WoF_BaseCharacterMovementComponent = StaticCast<UWoF_BaseCharacterMovementComp*>(GetCharacterMovement());
}

void AWizzardCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWizzardCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = YawRotator.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, Value);
		//AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AWizzardCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector RightVector = YawRotator.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, Value);
		//AddMovementInput(GetActorRightVector(), Value);
	}
}

void AWizzardCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AWizzardCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AWizzardCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	SpringArmComponent->TargetOffset += FVector(0.0f, 0.0f, HalfHeightAdjust);
}

void AWizzardCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	SpringArmComponent->TargetOffset -= FVector(0.0f, 0.0f, HalfHeightAdjust);
}

void AWizzardCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CharacterAttributesComponent->SetCanRestoreStamina(true);
}
