// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttributesComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WORLDOFFIVE_API UCharacterAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterAttributesComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnDeathEvent OnDeathEvent;

	bool IsAlive() { return CurrentHealth > 0.0f; }

	float GetCurrentStamina();
	void SetCanRestoreStamina(bool bIsCanRestore);
	void StaminaConsumption();
	bool IsOutOfStamina();

	float GetCurrentMana();
	void SetCanRestoreMana(bool bIsCanRestore);
	bool IsOutOfMana(float ManaConsumption);
	void ManaConsume(float SkillManaCoast);

	float GetHealthPercent() const;
	float GetStaminaPercent() const;
	float GetManaPercent() const;

	float SetBaseDamageReduse(float NewDamageReduse);
	float SetDamageReduseToDefaultValue();

protected:
	virtual void BeginPlay() override;		

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (UIMin = 0.0f))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (UIMin = "0"))
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (UIMin = "0"))
	float MaxMana = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (UIMin = "0"))
	float ManaRestoreSpeed = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (UIMin = "0"))
	float StaminaRestoreSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (UIMin = "0"))
	float StaminaConsumptionSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defence", meta = (UIMin = "0"))
	float BasePhysDamageReduse = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defence", meta = (UIMin = "0"))
	float BlockPhysDamageReduse = 1.0f;

private:
	float CurrentHealth = 0.0f;
	float CurrentStamina = 0.0f;
	float CurrentMana = 0.0f;

	void RestoreMana();
	bool bIsCanRestoreMana = true;
	void RestoreStamina();
	bool bIsCanRestoreStamina = true;

	UFUNCTION()
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	bool bIsBlocking = false;

	float DefaultDamageReduse;

	TWeakObjectPtr<class AWoF_BaseCharacter> CharacterOwner;
};
