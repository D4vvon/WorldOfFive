// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Component/CharacterAttributesComponent.h"
#include "../WoF_BaseCharacter.h"

UCharacterAttributesComponent::UCharacterAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DefaultDamageReduse = BasePhysDamageReduse;
}

void UCharacterAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(GetOwner()->IsA<AWoF_BaseCharacter>(), TEXT("Crush))"));
	CharacterOwner = StaticCast<AWoF_BaseCharacter*>(GetOwner());

	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;
	CurrentMana = MaxMana;

	CharacterOwner->OnTakeAnyDamage.AddDynamic(this, &UCharacterAttributesComponent::TakeAnyDamage);
}

void UCharacterAttributesComponent::RestoreMana()
{
	CurrentMana += ManaRestoreSpeed * 0.1;
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

	float FinalyDamageAmount = Damage; //add armor and other damage reduce
	if (bIsBlocking)
	{
		FinalyDamageAmount = Damage * (1.0f - BlockPhysDamageReduse);
	}
	else
	{
		FinalyDamageAmount = Damage * (1.0f - BasePhysDamageReduse);
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - FinalyDamageAmount, 0.0f, MaxHealth);
	CurrentStamina = FMath::Clamp(CurrentStamina - (Damage), 0.0f, MaxStamina);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), CurrentHealth));

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

	if (bIsCanRestoreMana && CurrentMana < MaxMana)
	{
		RestoreMana();
	}
	
	bIsBlocking = CharacterOwner->GetIsBlocking();
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

float UCharacterAttributesComponent::GetCurrentMana()
{
	return CurrentMana;
}

void UCharacterAttributesComponent::SetCanRestoreMana(bool bIsCanRestore)
{
	bIsCanRestoreMana = bIsCanRestore;
}

bool UCharacterAttributesComponent::IsOutOfMana(float ManaConsumption)
{
	return CurrentMana >= ManaConsumption;
}

void UCharacterAttributesComponent::ManaConsume(float SkillManaCoast)
{
	CurrentMana = FMath::Clamp(CurrentMana - SkillManaCoast, 0.0f, MaxMana);
}

float UCharacterAttributesComponent::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

float UCharacterAttributesComponent::GetStaminaPercent() const
{
	return CurrentStamina / MaxStamina;
}

float UCharacterAttributesComponent::GetManaPercent() const
{
	return CurrentMana / MaxMana;
}

float UCharacterAttributesComponent::SetBaseDamageReduse(float NewDamageReduse)
{
	return BasePhysDamageReduse *= NewDamageReduse;
}

float UCharacterAttributesComponent::SetDamageReduseToDefaultValue()
{
	return BasePhysDamageReduse = DefaultDamageReduse;
}

