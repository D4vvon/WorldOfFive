// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MeleeHitRegistrator.h"
#include "../WorldOfFive_Types.h"

UMeleeHitRegistrator::UMeleeHitRegistrator()
{
	PrimaryComponentTick.bCanEverTick = true;
	SphereRadius = 5.0f;
	SetCollisionProfileName(CollisionProfileNoCollision);
}

void UMeleeHitRegistrator::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsHitRegEnabled)
	{
		ProcessHitRegistration();
	}
	PreviousComponentLocation = GetComponentLocation();
}

void UMeleeHitRegistrator::SetIsHitRegEnabled(bool bIsEnabled_In)
{
	bIsHitRegEnabled = bIsEnabled_In;
}

void UMeleeHitRegistrator::ProcessHitRegistration()
{
	FVector CurrentLocation = GetComponentLocation();

	FHitResult HitResult;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bTraceComplex = true;
	CollisionQueryParams.AddIgnoredActor(GetOwner()->GetOwner());
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRadius);

	bool bHasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		PreviousComponentLocation,
		CurrentLocation,
		FQuat::Identity,
		ECC_Melee,
		CollisionShape,
		CollisionQueryParams,
		FCollisionResponseParams::DefaultResponseParam
	);

	if (bHasHit)
	{
		FVector Direction = (CurrentLocation - PreviousComponentLocation).GetSafeNormal();
		if (OnMeleeHitRegistrated.IsBound())
		{
			OnMeleeHitRegistrated.Broadcast(HitResult, Direction);
		}
	}
}
