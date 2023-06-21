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
	FVector ShotEnd = ShotStart + FiringRange * ShotDirection;

	switch (HitRegistration)
	{
	case EHitRegistrationType::HitScan:
	{
		bool bHasHit = HitScanShot(ShotStart, ShotEnd, ShotDirection);
		break;
	}
	case EHitRegistrationType::Projectile:
	{
		LaunchProjectile(MuzzleShotStart, ShotDirection);
		break;
	}
	}
	//DrawDebugLine(GetWorld(), MuzzleShotStart, ShotEnd, FColor::Green, false, 1.0f, 0, 3.0f); //DebugDraw
}

bool UWeaponBarellComponent::HitScanShot(FVector ShotStart, OUT FVector& ShotEnd, FVector ShotDirection)
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
	}	
	return bHasHit;
}

void UWeaponBarellComponent::LaunchProjectile(FVector& LaunchStart, FVector& LaunchDirection)
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
		DamageEvent.DamageTypeClass = DamageTypeClass;
		HitActor->TakeDamage(DamageAmount, DamageEvent, GetController(), GetOwner());
	}
}
