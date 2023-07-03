// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/Weapons/MeleeWeaponItem.h"
#include "../../../Characters/WoF_BaseCharacter.h"
#include "../../../Components/MeleeHitRegistrator.h"
#include "Engine/DamageEvents.h"
#include "../../../Characters/Component/WoF_BaseCharacterMovementComp.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Characters/Component/CharacterAttributesComponent.h"
#include "Components/CapsuleComponent.h"

AMeleeWeaponItem::AMeleeWeaponItem()
{
	EquippedSocketName = SocketCharacterWeapon;
}

void AMeleeWeaponItem::StartAttack(EMeleeAttackTypes AttackType)
{
	AWoF_BaseCharacter* CharacterOwner = GetCharacterOwner();
	if (!IsValid(CharacterOwner))
	{
		return;
	}

	HitActors.Empty();
	CurrentAttack = Attacks.Find(AttackType);

	UAnimMontage* RandAnimMontage = CurrentAttack->AttackMontages[FMath::RandRange(0, CurrentAttack->AttackMontages.Num() - 1)];
	UAnimInstance* CharacterAnimInstanse = CharacterOwner->GetMesh()->GetAnimInstance();
	
	if (CurrentAttack != nullptr && CharacterOwner->GetBaseCharacterMovementComponent()->IsCrouching())
	{
		if (IsValid(CharacterAnimInstanse))
		{
			float Duration = CharacterAnimInstanse->Montage_Play(CurrentAttack->CrouchedMontage, 1.0f, EMontagePlayReturnType::Duration);
			GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AMeleeWeaponItem::OnAttackTimerElapsed, Duration, false);
		}
	}
	else if (CurrentAttack != nullptr && IsValid(RandAnimMontage))
	{
		if (IsValid(CharacterAnimInstanse))
		{
			float Duration = CharacterAnimInstanse->Montage_Play(RandAnimMontage, 1.0f, EMontagePlayReturnType::Duration);
			GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AMeleeWeaponItem::OnAttackTimerElapsed, Duration, false);
		}
		else
		{
			OnAttackTimerElapsed();
		}
	}
}

void AMeleeWeaponItem::SetIsHitRegEnabled(bool bIsregEnabled)
{
	HitActors.Empty();
	for (UMeleeHitRegistrator* HitReg : HitRegistrators)
	{
		HitReg->SetIsHitRegEnabled(bIsregEnabled);
	}
}

void AMeleeWeaponItem::StartBlock()
{
	AWoF_BaseCharacter* CharacterOwner = GetCharacterOwner();
	if (!IsValid(CharacterOwner))
	{
		return;
	}

	UAnimInstance* CharacterAnimInstanse = CharacterOwner->GetMesh()->GetAnimInstance();
	 GetWorld()->GetTimerManager().ClearTimer(BlockingTimer);

	if (CharacterOwner->GetBaseCharacterMovementComponent()->IsCrouching())
	{
		float Duration = CharacterAnimInstanse->Montage_Play(CrouchBlockingMontage, 1.5f, EMontagePlayReturnType::Duration);
		GetWorld()->GetTimerManager().SetTimer(BlockingTimer, this, &AMeleeWeaponItem::StopBlock, Duration, false);
	}
	else
	{
		float Duration = CharacterAnimInstanse->Montage_Play(BlockingMontage, 1.5f, EMontagePlayReturnType::Duration);
		GetWorld()->GetTimerManager().SetTimer(BlockingTimer, this, &AMeleeWeaponItem::StopBlock, Duration, false);
	}
}

void AMeleeWeaponItem::StopBlock()
{
	AWoF_BaseCharacter* CharacterOwner = GetCharacterOwner();
	if (!IsValid(CharacterOwner))
	{
		return;
	}

	UAnimInstance* CharacterAnimInstanse = CharacterOwner->GetMesh()->GetAnimInstance();

	if (CharacterOwner->GetBaseCharacterMovementComponent()->IsCrouching())
	{
		CharacterAnimInstanse->Montage_Stop(0.2f, CrouchBlockingMontage);
	}
	else
	{
		CharacterAnimInstanse->Montage_Stop(0.2f, BlockingMontage);
	}

	CharacterOwner->SetIsBlocking(false);
}

void AMeleeWeaponItem::CastSkillBuff()
{
	AWoF_BaseCharacter* CharacterOwner = GetCharacterOwner();

	if (MeleeSkillBuff.bIsSkillOnCollDown == false && CharacterOwner->GetCharacterAttributesComponent()->IsOutOfMana(MeleeSkillBuff.ManaCoast))
	{
		MeleeSkillBuff.bIsSkillOnCollDown = true;
		CharacterOwner->GetCharacterAttributesComponent()->ManaConsume(MeleeSkillBuff.ManaCoast);
		CharacterOwner->PlayAnimMontage(MeleeSkillBuff.SkillMontage);

		switch (MeleeSkillBuff.SkillType)
		{
		case EMeleeSkillTypes::Defense:
		{
			BuffSkillVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(MeleeSkillBuff.SkillVFX, GetCharacterOwner()->GetSkillPointLocation(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::KeepRelativeOffset, false, true, ENCPoolMethod::None, true);

			GetWorld()->GetTimerManager().SetTimer(MeleeSkillBuff.SkillCasting, this, &AMeleeWeaponItem::EndSkill, MeleeSkillBuff.DefDuration, false);
			GetWorld()->GetTimerManager().SetTimer(MeleeSkillBuff.SkillCoolDownTimer, this, &AMeleeWeaponItem::EndCoolDownBuff, MeleeSkillBuff.SkillCoolDown, false);

			CharacterOwner->GetCharacterAttributesComponent()->SetBaseDamageReduse(2.0f);
			break;
		}
		case EMeleeSkillTypes::Buff:
		{
			BuffSkillVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MeleeSkillBuff.SkillVFX, GetOwner()->GetActorLocation(), FRotator::ZeroRotator, FVector(1.0f, 1.0f, 1.0f), false, true, ENCPoolMethod::None, true);

			GetWorld()->GetTimerManager().SetTimer(MeleeSkillBuff.SkillCoolDownTimer, this, &AMeleeWeaponItem::EndCoolDownBuff, MeleeSkillBuff.SkillCoolDown, false);
			break;
		}
		default:
			break;
		}
	}
}

void AMeleeWeaponItem::CastSkillAttack()
{
	AWoF_BaseCharacter* CharacterOwner = GetCharacterOwner();

	if (MeleeSkillAttack.bIsSkillOnCollDown == false && CharacterOwner->GetCharacterAttributesComponent()->IsOutOfMana(MeleeSkillAttack.ManaCoast))
	{
		
		MeleeSkillAttack.bIsSkillOnCollDown = true;
		GetWorld()->GetTimerManager().SetTimer(MeleeSkillAttack.SkillCoolDownTimer, this, &AMeleeWeaponItem::EndCoolDownAttack, MeleeSkillAttack.SkillCoolDown, false);
		CharacterOwner->GetCharacterAttributesComponent()->ManaConsume(MeleeSkillAttack.ManaCoast);
		CharacterOwner->PlayAnimMontage(MeleeSkillAttack.SkillMontage);
		
		AttackSkillVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MeleeSkillAttack.SkillVFX, GetOwner()->GetActorLocation() - CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + FVector(55.0f, 100.0f, 0.0f), GetOwner()->GetActorRotation(), FVector(1.0f), false, true, ENCPoolMethod::None, true);
	}
}

void AMeleeWeaponItem::EndSkill()
{
	AWoF_BaseCharacter* CharacterOwner = GetCharacterOwner();

	if (IsValid(BuffSkillVFXComponent))
	{
		BuffSkillVFXComponent->DestroyComponent();
	}
	 CharacterOwner->GetCharacterAttributesComponent()->SetDamageReduseToDefaultValue();
}

void AMeleeWeaponItem::EndCoolDownBuff()
{
	MeleeSkillBuff.bIsSkillOnCollDown = false;
}

void AMeleeWeaponItem::EndCoolDownAttack()
{
	MeleeSkillAttack.bIsSkillOnCollDown = false;
}

void AMeleeWeaponItem::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UMeleeHitRegistrator>(HitRegistrators);
	for (UMeleeHitRegistrator* HitReg : HitRegistrators)
	{
		HitReg->OnMeleeHitRegistrated.AddUFunction(this, FName("ProcessHit"));
	}
}

void AMeleeWeaponItem::ProcessHit(const FHitResult& HitResult, const FVector& Direction)
{
	if (CurrentAttack == nullptr)
	{
		return;
	}

	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor))
	{
		return;
	}

	if (HitActors.Contains(HitActor))
	{
		return;
	}

	FPointDamageEvent DamageEvent;
	DamageEvent.HitInfo = HitResult;
	DamageEvent.ShotDirection = Direction;
	DamageEvent.DamageTypeClass = CurrentAttack->DamageTypeClass;

	AWoF_BaseCharacter* CharacterOwner = GetCharacterOwner();
	AController* Controller = IsValid(CharacterOwner) ? CharacterOwner->GetController<AController>() : nullptr;
	HitActor->TakeDamage(CurrentAttack->DamageAmount, DamageEvent, Controller, GetOwner());

	HitActors.Add(HitActor);
}

void AMeleeWeaponItem::OnAttackTimerElapsed()
{
	CurrentAttack = nullptr;
	SetIsHitRegEnabled(false);
}
