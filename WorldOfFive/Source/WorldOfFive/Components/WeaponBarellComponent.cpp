// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponBarellComponent.h"
#include "WorldOfFive_Types.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


void UWeaponBarellComponent::Shot(FVector ShotStart, FVector ShotDirection, AController* Controller)
{
	FVector MuzzleShotStart = GetComponentLocation();
	FVector ShotEnd = ShotStart + FiringRange * ShotDirection;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, ShotStart, ShotEnd, ECC_Bullet))
	{
		ShotEnd = HitResult.ImpactPoint;
		AActor* HitActor = HitResult.GetActor();
		if (IsValid(HitActor))
		{
			HitActor->TakeDamage(DamageAmount, FDamageEvent{}, Controller, GetOwner());
		}
		FVector TopVFXOffset = FVector(0.0f, 50.0f, 0.0f);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ResultVFX, ShotEnd + TopVFXOffset, FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, FColor::Red, false, 1.0f); //DebugDraw
	}
	DrawDebugLine(GetWorld(), MuzzleShotStart, ShotEnd, FColor::Green, false, 1.0f, 0, 3.0f); //DebugDraw
}
