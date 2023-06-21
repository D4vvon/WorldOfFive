// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ExplosionComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../../../../../../UE_5.1/Engine/Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"


void UExplosionComponent::Explode(AController* Controller)
{
	if (OnExplosion.IsBound())
	{
		OnExplosion.Broadcast();
	}

	if (IsValid(ExplodeVFX))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplodeVFX, GetComponentLocation(), FRotator::ZeroRotator);
	}

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetOwner());

	UGameplayStatics::ApplyRadialDamageWithFalloff
	(
		GetWorld(),
		MaxDamage,
		MinDamage,
		GetComponentLocation(),
		InnerRadius,
		OuterRaius,
		DamageFallOff,
		DamageTypeClass,
		IgnoredActors,
		GetOwner(),
		Controller,
		ECC_Visibility
	);
}
