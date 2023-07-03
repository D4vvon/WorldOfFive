// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GreatSwordCharacter.h"
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
#include "Actors/Equipment/Weapons/MeleeWeaponItem.h"

AGreatSwordCharacter::AGreatSwordCharacter(const FObjectInitializer& ObjectInitializer)
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

	CharacterSkillPointLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SkillLocation"));
	CharacterSkillPointLocation->SetupAttachment(RootComponent);
}

void AGreatSwordCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGreatSwordCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = YawRotator.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, Value);
		//AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGreatSwordCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector RightVector = YawRotator.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, Value);
		//AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGreatSwordCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AGreatSwordCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AGreatSwordCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	SpringArmComponent->TargetOffset += FVector(0.0f, 0.0f, HalfHeightAdjust);
}

void AGreatSwordCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	SpringArmComponent->TargetOffset -= FVector(0.0f, 0.0f, HalfHeightAdjust);
}

void AGreatSwordCharacter::EndRoll()
{
	SetUnCrouching();
	GetBaseCharacterMovementComponent()->bOrientRotationToMovement = 0;
	bUseControllerRotationYaw = true;
}

void AGreatSwordCharacter::Roll()
{
	if (GetBaseCharacterMovementComponent()->Velocity != FVector::ZeroVector && GetBaseCharacterMovementComponent()->bOrientRotationToMovement == 0)
	{
		GetBaseCharacterMovementComponent()->bOrientRotationToMovement = 1;
		bUseControllerRotationYaw = false;
		SetCrouching();
		float Duration = PlayAnimMontage(RollAnimMontage);
		if (Duration > 0.0f)
		{
			GetWorld()->GetTimerManager().SetTimer(RollMontageTimer, this, &AGreatSwordCharacter::EndRoll, Duration, false);
		}
		else
		{
			GetBaseCharacterMovementComponent()->bOrientRotationToMovement = 0;
			bUseControllerRotationYaw = true;
		}
	}
}

void AGreatSwordCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CharacterAttributesComponent->SetCanRestoreStamina(true);
	CharacterAttributesComponent->SetCanRestoreMana(true);
}

void AGreatSwordCharacter::EquipMeleeWeapon()
{
	if (CharacterEquipmentComponent->IsEquip())
	{
		CharacterEquipmentComponent->UnequipCurrentItem();
		GetBaseCharacterMovementComponent()->bOrientRotationToMovement = 1;
		bUseControllerRotationYaw = 0;
	}
	else if (!CharacterEquipmentComponent->IsEquip())
	{
		CharacterEquipmentComponent->EquipMeleeItem();
		GetBaseCharacterMovementComponent()->bOrientRotationToMovement = 0;
		bUseControllerRotationYaw = 1;
	}
}

void AGreatSwordCharacter::AttackWeaponMelee()
{
	AMeleeWeaponItem* CurrentMeleeWeapon = CharacterEquipmentComponent->GetCurrentMeleeWeapon();
	if (IsValid(CurrentMeleeWeapon))
	{
		CurrentMeleeWeapon->StartAttack(EMeleeAttackTypes::WeaponAttack);
	}
}

void AGreatSwordCharacter::AttackBodyMelee()
{
	AMeleeWeaponItem* CurrentMeleeWeapon = CharacterEquipmentComponent->GetCurrentMeleeWeapon();
	if (IsValid(CurrentMeleeWeapon))
	{
		CurrentMeleeWeapon->StartAttack(EMeleeAttackTypes::MeleeBodyAttack);
	}
}

void AGreatSwordCharacter::Blocking()
{
	AMeleeWeaponItem* CurrentMeleeWeapon = CharacterEquipmentComponent->GetCurrentMeleeWeapon();
	if (CharacterAttributesComponent->GetCurrentStamina() < 10.0f)
	{
		return;
	}
	if (IsValid(CurrentMeleeWeapon))
	{
		if (!bIsBlocking)
		{
			CurrentMeleeWeapon->StartBlock();
			bIsBlocking = true;
			return;
		}
		else
		{
			CurrentMeleeWeapon->StopBlock();
			bIsBlocking = false;
			return;
		}
	}
}

bool AGreatSwordCharacter::GetIsBlocking()
{
	return bIsBlocking;
}

void AGreatSwordCharacter::SetIsBlocking(bool NewIsBlocking)
{
	bIsBlocking = NewIsBlocking;
}

void AGreatSwordCharacter::CastSkillBuff()
{
	AMeleeWeaponItem* CurrentMeleeWeapon = CharacterEquipmentComponent->GetCurrentMeleeWeapon();
	if (IsValid(CurrentMeleeWeapon))
	{
		CurrentMeleeWeapon->CastSkillBuff();
	}
}

void AGreatSwordCharacter::CastSkillAttack()
{
	AMeleeWeaponItem* CurrentMeleeWeapon = CharacterEquipmentComponent->GetCurrentMeleeWeapon();
	if (IsValid(CurrentMeleeWeapon))
	{
		CurrentMeleeWeapon->CastSkillAttack();
	}
}

class USceneComponent* AGreatSwordCharacter::GetSkillPointLocation()
{
	return CharacterSkillPointLocation;
}

