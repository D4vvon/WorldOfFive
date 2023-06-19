// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Component/CharacterAttributesComponent.h"
#include "../WoF_BaseCharacter.h"

UCharacterAttributesComponent::UCharacterAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(GetOwner()->IsA<AWoF_BaseCharacter>(), TEXT("Crush))"));
	BaseCharacterOwner = StaticCast<AWoF_BaseCharacter*>(GetOwner());

	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;

	BaseCharacterOwner->OnTakeAnyDamage.AddDynamic(this, &UCharacterAttributesComponent::TakeAnyDamage);
}

void UCharacterAttributesComponent::RestoreStamina()
{
	CurrentStamina += StaminaRestoreSpeed * 0.1;
}

void UCharacterAttributesComponent::TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (!IsAlive())
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	if (CurrentHealth <= 0.0f)
	{
		if (OnDeathEvent.IsBound())
		{
			OnDeathEvent.Broadcast();
		}
	}
}

void UCharacterAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsAlive())
	{
		return;
	}

	if (bIsCanRestoreStamina && CurrentStamina < MaxStamina)
	{
		RestoreStamina();
	}
}

float UCharacterAttributesComponent::GetCurrentStamina()
{
	return CurrentStamina;
}

void UCharacterAttributesComponent::SetCanRestoreStamina(bool bIsCanRestore)
{
	bIsCanRestoreStamina = bIsCanRestore;
}

void UCharacterAttributesComponent::StaminaConsumption()
{
	CurrentStamina = FMath::Clamp(CurrentStamina - StaminaConsumptionSpeed * 0.2, 0.0f, MaxStamina);
}

bool UCharacterAttributesComponent::IsOutOfStamina()
{
	return CurrentStamina < 20 ? true : false;
}

float UCharacterAttributesComponent::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

