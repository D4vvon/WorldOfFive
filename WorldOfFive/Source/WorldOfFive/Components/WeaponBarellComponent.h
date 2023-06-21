// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WorldOfFive_Types.h"
#include "Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "WeaponBarellComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WORLDOFFIVE_API UWeaponBarellComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	void Shot(FVector ShotStart, FVector ShotDirection, AController* Controller, FSkillParameters SkillParams);


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barell attributes")
	float FiringRange = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barell attributes")
	float DamageAmount = 40.0f;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barell attributes")
	class UNiagaraSystem* ResultVFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barell attributes | Hit reg")
	TSubclassOf<class UDamageType> DamageTypeClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barell attributes | Hit reg")
	EHitRegistrationType HitRegistration = EHitRegistrationType::HitScan;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barell attributes | Hit reg", meta = (EditCondition = "HitRegistration == EHitRegistrationType::Projectile"))
	TSubclassOf<class AWoF_Projectile> ProjectileClass;

private:
	APawn* GetOwningPawn();
	AController* GetController();

	UFUNCTION()
	void ProcessHit(const FHitResult& HitResult, const FVector& Direction);

	bool HitScanShot(FVector ShotStart, OUT FVector& ShotEnd, FVector ShotDirection);

	void LaunchProjectile(FVector& LaunchStart, FVector& LaunchDirection);

};
