// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/WoF_Projectile.h"
#include "../../../../../../../UE_5.1/Engine/Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../UE_5.1/Engine/Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

AWoF_Projectile::AWoF_Projectile()
{
	CollisionConponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionConponent->InitSphereRadius(5.0f);
	CollisionConponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionConponent->SetCollisionResponseToAllChannels(ECR_Block);
	SetRootComponent(CollisionConponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
}

void AWoF_Projectile::LaunchProjectile(FVector Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
	CollisionConponent->IgnoreActorWhenMoving(GetOwner(), true);
}

void AWoF_Projectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionConponent->OnComponentHit.AddDynamic(this, &AWoF_Projectile::OnCollisionHit);
}

void AWoF_Projectile::OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OnProjectileHit.IsBound())
	{
		OnProjectileHit.Broadcast(Hit, ProjectileMovementComponent->Velocity.GetSafeNormal());
	}
}

