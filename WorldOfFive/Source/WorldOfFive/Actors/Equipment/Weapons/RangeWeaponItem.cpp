// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "Components/WeaponBarellComponent.h"
#include "Characters/WoF_BaseCharacter.h"

ARangeWeaponItem::ARangeWeaponItem()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon mesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	WeaponBarell = CreateDefaultSubobject<UWeaponBarellComponent>(TEXT("Weapon barell"));
	WeaponBarell->SetupAttachment(WeaponMesh);
}

void ARangeWeaponItem::FireSetup()
{
	GetWorld()->GetTimerManager().ClearTimer(Spell_BurningEarthTimer);
	AWoF_BaseCharacter* CharacterOwner = StaticCast<AWoF_BaseCharacter*>(GetOwner());
	
	float Duration = CharacterOwner->PlayAnimMontage(CharacterFireMontage);
	if (Duration > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(Spell_BurningEarthTimer, this, &ARangeWeaponItem::Fire, Duration, false);
		if (IsValid(WeaponAnimMontage))
		{
			PlayAnimMontage(WeaponAnimMontage);
		}
	}
	else
	{
		Fire();
	}
}

void ARangeWeaponItem::Fire()
{	
	 AWoF_BaseCharacter* CharacterOwner = StaticCast<AWoF_BaseCharacter*>(GetOwner());
	 APlayerController* Controller = CharacterOwner->GetController<APlayerController>();
	 if (!IsValid(Controller))
	 {
		return;
	 }

	 FVector PlayerViewPoint;
	 FRotator PlayerViewRotation;
	 Controller->GetPlayerViewPoint(PlayerViewPoint, PlayerViewRotation);

	 FVector ViewDirection = PlayerViewRotation.RotateVector(FVector::ForwardVector);

	WeaponBarell->Shot(PlayerViewPoint, ViewDirection, Controller);
}

float ARangeWeaponItem::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	UAnimInstance* WeaponAnimInstance = WeaponMesh->GetAnimInstance();
	return WeaponAnimInstance->Montage_Play(AnimMontage);
}
