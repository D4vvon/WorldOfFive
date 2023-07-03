// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponBarellComponent.h"
#include "WorldOfFive_Types.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Actors/Projectiles/WoF_Projectile.h"
#include "Actors/Equipment/Weapons/RangeWeaponItem.h"


void UWeaponBarellComponent::Shot(FVector ShotStart, FVector ShotDirection, AController* Controller, FSkillParameters SkillParams)
{
	FVector MuzzleShotStart = GetComponentLocation();
	//ShotDirection = MuzzleShotStart;
	FVector ShotEnd = ShotStart + SkillParams.FiringRange * ShotDirection;

	//switch (HitRegistration)
	switch (SkillParams.HitType)
	{
	case EHitRegistrationType::HitScan:
	{
		bool bHasHit = false;
		if (SkillParams.SkillType == EWizzardSphereSkillType::Casual)
		{
			//bHasHit = HitScanMultishot(ShotStart, ShotEnd, ShotDirection, SkillParams.ResultVFX, SkillParams.FiringRange);
			FVector SpawningOffset = FVector(0.0f, 100.0f, -10.0f);
			AActor* ExplodeActor = GetWorld()->SpawnActor<AActor>(SkillParams.ActorClass, MuzzleShotStart + SpawningOffset, FRotator::ZeroRotator);
			if (IsValid(ExplodeActor))
			{
				ExplodeActor->SetOwner(GetOwningPawn());
			}
		}
		else if (SkillParams.SkillType == EWizzardSphereSkillType::AOEDamge)
		{
			bHasHit = HitScanShot(ShotStart, ShotEnd, ShotDirection, SkillParams.ResultVFX, SkillParams.ActorClass);
		}
		else if (SkillParams.SkillType == EWizzardSphereSkillType::Field)
		{

		}
		else if (SkillParams.SkillType == EWizzardSphereSkillType::Ray)
		{

		}
		//bHasHit = HitScanShot(ShotStart, ShotEnd, ShotDirection, SkillParams.ResultVFX);
		break;
	}
	case EHitRegistrationType::Projectile:
	{
		LaunchProjectile(MuzzleShotStart, ShotDirection, SkillParams.ProjectileClass);
		break;
	}
	}
	//DrawDebugLine(GetWorld(), MuzzleShotStart, ShotEnd, FColor::Green, false, 1.0f, 0, 3.0f); //DebugDraw
}

bool UWeaponBarellComponent::HitScanShot(FVector ShotStart, OUT FVector& ShotEnd, FVector ShotDirection, UNiagaraSystem* ResultVFX, TSubclassOf<AActor> ActorClass)
{
	FHitResult HitResult;
	bool bHasHit = GetWorld()->LineTraceSingleByChannel(HitResult, ShotStart, ShotEnd, ECC_Bullet);
	if (bHasHit)
	{
		ShotEnd = HitResult.ImpactPoint;
		ProcessHit(HitResult, ShotDirection);

		FVector TopVFXOffset = FVector(0.0f, 50.0f, 0.0f);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ResultVFX, ShotEnd + TopVFXOffset, FRotator::ZeroRotator);
		//DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, FColor::Red, false, 1.0f); //DebugDraw
		AActor* ExplodeActor = GetWorld()->SpawnActor<AActor>(ActorClass, ShotEnd, FRotator::ZeroRotator);
		if (IsValid(ExplodeActor))
		{
			ExplodeActor->SetOwner(GetOwningPawn());
		}
	}	
	return bHasHit;
}

bool UWeaponBarellComponent::HitScanMultishot(FVector ShotStart, OUT FVector& ShotEnd, FVector ShotDirection, UNiagaraSystem* ResultVFX, float FiringSkillRange)
{
	FHitResult HitResult;
	bool bHasHit = GetWorld()->LineTraceSingleByChannel(HitResult, ShotStart, ShotEnd, ECC_Bullet);
	if (bHasHit)
	{
		ShotEnd = HitResult.ImpactPoint;
		ProcessHit(HitResult, ShotDirection);

		FVector TopVFXOffset = FVector(0.0f, 50.0f, 0.0f);
		DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, FColor::Red, false, 1.0f); //DebugDraw
	}
	UNiagaraComponent* HitVfx = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ResultVFX, ShotStart, FRotator::ZeroRotator);
	return bHasHit;
}

void UWeaponBarellComponent::LaunchProjectile(FVector& LaunchStart, FVector& LaunchDirection, TSubclassOf<class AWoF_Projectile> ProjectileClass)
{
	AWoF_Projectile* Projectile = GetWorld()->SpawnActor<AWoF_Projectile>(ProjectileClass, LaunchStart, LaunchDirection.ToOrientationRotator());
	if (IsValid(Projectile))
	{
		Projectile->SetOwner(GetOwningPawn());
		Projectile->OnProjectileHit.AddDynamic(this, &UWeaponBarellComponent::ProcessHit);
		Projectile->LaunchProjectile(LaunchDirection.GetSafeNormal());
	}
}

APawn* UWeaponBarellComponent::GetOwningPawn()
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (IsValid(PawnOwner))
	{
		PawnOwner = Cast<APawn>(GetOwner()->GetOwner());
	}
	return PawnOwner;
}

AController* UWeaponBarellComponent::GetController()
{
	APawn* PawnOwner = GetOwningPawn();
	return IsValid(PawnOwner) ? PawnOwner->GetController() : nullptr;
}

void UWeaponBarellComponent::ProcessHit(const FHitResult& HitResult, const FVector& Direction)
{
	AActor* HitActor = HitResult.GetActor();
	if (IsValid(HitActor))
	{
		FPointDamageEvent DamageEvent;
		DamageEvent.HitInfo = HitResult;
		DamageEvent.ShotDirection = Direction;
		HitActor->TakeDamage(DamageAmount, DamageEvent, GetController(), GetOwner());
	}
}
