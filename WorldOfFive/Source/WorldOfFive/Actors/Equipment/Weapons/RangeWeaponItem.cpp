// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "Components/WeaponBarellComponent.h"
#include "Characters/WoF_BaseCharacter.h"
#include "WorldOfFive_Types.h"

ARangeWeaponItem::ARangeWeaponItem()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon mesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	WeaponBarell = CreateDefaultSubobject<UWeaponBarellComponent>(TEXT("Weapon barell"));
	WeaponBarell->SetupAttachment(WeaponMesh);

	EquippedSocketName = SocketCharacterWeapon;
}

void ARangeWeaponItem::BeginPlay()
{
	Super::BeginPlay();
	CreateSkillsLoadout();
	SetSkillToWeapon(EWizzardSphereSkillType::Missle);
}

void ARangeWeaponItem::FireSetup()
{
	//GetWorld()->GetTimerManager().ClearTimer(SpellTimer);
	AWoF_BaseCharacter* CharacterOwner = StaticCast<AWoF_BaseCharacter*>(GetOwner());
	
	//float Duration = CharacterOwner->PlayAnimMontage(CharacterFireMontage);
	float Duration = CharacterOwner->PlayAnimMontage(CurrentSkillParams.CharacterCastingAnimMontage);
	if (CurrentSkillParams.SkillDelay > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(SpellTimer, this, &ARangeWeaponItem::Fire, Duration * CurrentSkillParams.SkillDelay, false);
		if (IsValid(WeaponAnimMontage))
		{
			PlayAnimMontage(WeaponAnimMontage);
		}
	}
}

void ARangeWeaponItem::StartFire()
{
	FireSetup();
	//if (WeaponFireMode == EWeaponFireMode::Auto)
	//{
	//	GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
	//	GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &ARangeWeaponItem::FireSetup, GetShotTimerInterval(), true);
	//}
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
	WeaponBarell->Shot(PlayerViewPoint, ViewDirection, Controller, CurrentSkillParams);
}

void ARangeWeaponItem::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
}

void ARangeWeaponItem::NextSkill()
{
	uint32 CurrentSkillIndex = (uint32)CurrentSkillType;
	uint32 NextSkillIndex = NextSkillsArrayIndex(CurrentSkillIndex);
	if (NextSkillIndex == (uint32)EWizzardSphereSkillType::None)
	{
		NextSkillIndex = NextSkillsArrayIndex(NextSkillIndex);
	}
	if (CurrentSkillIndex != NextSkillIndex)
	{
		SetSkillToWeapon((EWizzardSphereSkillType)NextSkillIndex);
	}
}

void ARangeWeaponItem::PreviousSkill()
{
	uint32 CurrentSkillIndex = (uint32)CurrentSkillType;
	uint32 PreviousSkillIndex = PreviousSkillsArrayIndex(CurrentSkillIndex);
	if (PreviousSkillIndex == (uint32)EWizzardSphereSkillType::None)
	{
		PreviousSkillIndex = PreviousSkillsArrayIndex(PreviousSkillIndex);
	}
	if (CurrentSkillIndex != PreviousSkillIndex)
	{
		SetSkillToWeapon((EWizzardSphereSkillType)PreviousSkillIndex);
	}
}

void ARangeWeaponItem::SetSkillToWeapon(EWizzardSphereSkillType Skill)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Skill: %i"), (uint32)CurrentSkillType));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Skill: %i"), SkillsArray.Num()));
	if (CurrentSkillType != Skill)
	{
		CurrentSkillType = Skill;
		CurrentSkillParams = SkillsArray[(uint32)Skill];
	}
}

void ARangeWeaponItem::CreateSkillsLoadout()
{
	SkillsArray.AddZeroed((uint32)EWizzardSphereSkillType::MAX);
	for (const TPair<EWizzardSphereSkillType, FSkillParameters>& SkillPair : SkillsMap)
	{
		if (!SkillsMap.Contains(SkillPair.Key))
		//if (SkillsArray.Contains((uint32)SkillPair.Key))
		{
			continue;
		}
		SkillsArray[(uint32)SkillPair.Key] = SkillPair.Value;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("PairKey: %i"), (uint32)SkillPair.Key));
	}
}

float ARangeWeaponItem::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	UAnimInstance* WeaponAnimInstance = WeaponMesh->GetAnimInstance();
	return WeaponAnimInstance->Montage_Play(AnimMontage);
}

float ARangeWeaponItem::GetShotTimerInterval()
{
	return 60.0f / RateOfFire;
}

uint32 ARangeWeaponItem::NextSkillsArrayIndex(uint32 CurrentIndex)
{
	if (CurrentIndex == SkillsArray.Num() - 1)
	{
		return 0;
	}
	else
	{
		return CurrentIndex + 1;
	}
}

uint32 ARangeWeaponItem::PreviousSkillsArrayIndex(uint32 CurrentIndex)
{
	if (CurrentIndex == 0)
	{
		return SkillsArray.Num() - 1;
	}
	else
	{
		return CurrentIndex - 1;
	}
}
