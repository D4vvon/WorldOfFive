// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ExplosionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExplosion);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WORLDOFFIVE_API UExplosionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void Explode(AController* Controller);

	UPROPERTY(BlueprintAssignable)
	FOnExplosion OnExplosion;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float MaxDamage = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float MinDamage = 70.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float DamageFallOff = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	TSubclassOf<class UDamageType> DamageTypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion | Radius")
	float InnerRadius = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion | Radius")
	float OuterRaius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	class UNiagaraSystem* ExplodeVFX;


};
