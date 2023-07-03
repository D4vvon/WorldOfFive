// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "MeleeHitRegistrator.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMeleeHitRegistred, const FHitResult&, const FVector&)

UCLASS(meta = (BlueprintSpawnableComponent))
class WORLDOFFIVE_API UMeleeHitRegistrator : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UMeleeHitRegistrator();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ProcessHitRegistration();

	void SetIsHitRegEnabled(bool bIsEnabled_In);

	FOnMeleeHitRegistred OnMeleeHitRegistrated;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee hit registration")
	bool bIsHitRegEnabled = false;

private:
	FVector PreviousComponentLocation = FVector::ZeroVector;
};