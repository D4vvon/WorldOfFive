// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WoF_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/WoF_BaseCharacterMovementComp.h"
#include "GameFramework/Character.h"
#include "Component/CharacterAttributesComponent.h"
#include "WorldOfFive_Types.h"
#include "Engine/DamageEvents.h"
#include "Component/CharacterEquipmentComponent.h"

AWoF_BaseCharacter::AWoF_BaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWoF_BaseCharacterMovementComp>(ACharacter::CharacterMovementComponentName))
{
	WoF_BaseCharacterMovementComponent = StaticCast<UWoF_BaseCharacterMovementComp*>(GetCharacterMovement());
	CharacterAttributesComponent = CreateDefaultSubobject<UCharacterAttributesComponent>(TEXT("Character attributes component"));
	CharacterEquipmentComponent = CreateDefaultSubobject<UCharacterEquipmentComponent>(TEXT("Character equipment component"));
}

void AWoF_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributesComponent->OnDeathEvent.AddUObject(this, &AWoF_BaseCharacter::OnDeath);
}

void AWoF_BaseCharacter::ChangeCrouchState()
{
	//if (GetBaseCharacterMovementComponent()->bOrientRotationToMovement)
	//{
		if (GetCharacterMovement()->IsCrouching())
		{
			SetUnCrouching();
		}
		else
		{
			SetCrouching();
		}
	//}
}

void AWoF_BaseCharacter::SetCrouching()
{
	Crouch();
}

void AWoF_BaseCharacter::SetUnCrouching()
{
	UnCrouch();
}

void AWoF_BaseCharacter::EndRoll()
{
	SetUnCrouching();
	GetBaseCharacterMovementComponent()->bOrientRotationToMovement = 0;
	bUseControllerRotationYaw = true;
}

void AWoF_BaseCharacter::Roll()
{
	if (GetBaseCharacterMovementComponent()->Velocity != FVector::ZeroVector)
	{
		GetBaseCharacterMovementComponent()->bOrientRotationToMovement = 1;
		bUseControllerRotationYaw = false;
		SetCrouching();
		float Duration = PlayAnimMontage(RollAnimMontage);
		if (Duration > 0.0f)
		{
			GetWorld()->GetTimerManager().SetTimer(RollMontageTimer, this, &AWoF_BaseCharacter::EndRoll, Duration, false);
		}
		else
		{
			GetBaseCharacterMovementComponent()->bOrientRotationToMovement = 0;
			bUseControllerRotationYaw = true;
		}
	}
}

void AWoF_BaseCharacter::StartSprint()
{
	bIsSprintRequested = true;
	if (bIsCrouched)
	{
		UnCrouch();
	}
}

void AWoF_BaseCharacter::StopSprint()
{
	bIsSprintRequested = false;
}

void AWoF_BaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TryChangeSprintState();
	if (bIsSprintRequested)
	{
		CharacterAttributesComponent->StaminaConsumption();
	}
	else
	{
		CharacterAttributesComponent->SetCanRestoreStamina(true);
	}
	if (CharacterAttributesComponent->GetCurrentStamina() < 5.0f)
	{
		bIsSprintRequested = false;
	}
}

UCharacterAttributesComponent* AWoF_BaseCharacter::GetCharacterAttributesComponent() const
{
	return CharacterAttributesComponent;
}

UCharacterEquipmentComponent* AWoF_BaseCharacter::GetCharacterEquipmentComponent() const
{
	return CharacterEquipmentComponent;
}

void AWoF_BaseCharacter::Falling()
{
	GetCharacterMovement()->bNotifyApex = true;
}

void AWoF_BaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	float FallHeight = (CurrentFallApex - GetActorLocation()).Z * 0.01f;
	if (IsValid(FallDamageCurve))
	{
		float DamageAmount = FallDamageCurve->GetFloatValue(FallHeight) ;
		TakeDamage(DamageAmount, FDamageEvent(), GetController(), Hit.GetActor());
	}
}

void AWoF_BaseCharacter::NotifyJumpApex()
{
	Super::NotifyJumpApex();
	CurrentFallApex = GetActorLocation();
}

void AWoF_BaseCharacter::Fire()
{
	CharacterEquipmentComponent->Fire();
}

void AWoF_BaseCharacter::TryChangeSprintState()
{
	if (bIsSprintRequested && !WoF_BaseCharacterMovementComponent->IsSprinting() && CanSprint())
	{
		WoF_BaseCharacterMovementComponent->StartSprint();
	}

	if (!bIsSprintRequested && WoF_BaseCharacterMovementComponent->IsSprinting())
	{
		WoF_BaseCharacterMovementComponent->StopSprint();
	}
}

void AWoF_BaseCharacter::EnableRagdoll()
{
	GetMesh()->SetCollisionProfileName(CollisionProfileRagdoll);
	GetMesh()->SetSimulatePhysics(true);
}

void AWoF_BaseCharacter::OnDeath()
{
	float Duration = PlayAnimMontage(OnDeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	if (Duration == 0.0f)
	{
		EnableRagdoll();
	}
}

bool AWoF_BaseCharacter::CanSprint()
{
	if (bIsCanSprint == false)
	{
		return false;
	}

	float CurrentStamina = CharacterAttributesComponent->GetCurrentStamina();
	if (CurrentStamina > 10.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}