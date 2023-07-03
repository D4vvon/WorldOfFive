// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Equipment/EquipableItem.h"
#include "../../../WorldOfFive_Types.h"
#include "MeleeWeaponItem.generated.h"

USTRUCT(BlueprintType)
struct FMeleeAttackDescription 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	TSubclassOf<class UDamageType> DamageTypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	float DamageAmount = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	TArray<class UAnimMontage*> AttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	class UAnimMontage* CrouchedMontage;
};

USTRUCT(BlueprintType)
struct FMeleeSkillDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	class UTexture2D* SkillTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	EMeleeSkillTypes SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (EditCondition = "SkillType == EMeleeSkillTypes::Defense"))
	float DefDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (EditCondition = "SkillType == EMeleeSkillTypes::Buff"))
	float BuffAmount = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (EditCondition = "SkillType == EMeleeSkillTypes::Attack"))
	float DamageAmount = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	class UAnimMontage* SkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float SkillCoolDown = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float ManaCoast = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	class UNiagaraSystem* SkillVFX;

	bool bIsSkillOnCollDown = false;

	FTimerHandle SkillCasting;
	FTimerHandle SkillCoolDownTimer;
};

class UMeleeHitRegistrator;
UCLASS(Blueprintable)
class WORLDOFFIVE_API AMeleeWeaponItem : public AEquipableItem
{
	GENERATED_BODY()
	
public:
	AMeleeWeaponItem();

	void StartAttack(EMeleeAttackTypes AttackType);

	void SetIsHitRegEnabled(bool bIsregEnabled);

	void StartBlock();
	void StopBlock();

	void CastSkillBuff();
	void CastSkillAttack();
	void EndSkill();
	void EndCoolDownBuff();
	void EndCoolDownAttack();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee attack")
	TMap<EMeleeAttackTypes, FMeleeAttackDescription> Attacks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
	class UAnimMontage* BlockingMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
	class UAnimMontage* CrouchBlockingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	FMeleeSkillDescription MeleeSkillBuff;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	FMeleeSkillDescription MeleeSkillAttack;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ProcessHit(const FHitResult& HitResult, const FVector& Direction);

	class UNiagaraComponent* BuffSkillVFXComponent;
	class UNiagaraComponent* AttackSkillVFXComponent;

	TArray<UMeleeHitRegistrator*> HitRegistrators;
	TSet<AActor*> HitActors;

	void OnAttackTimerElapsed();
	FTimerHandle AttackTimer;

	FMeleeAttackDescription* CurrentAttack;

	FTimerHandle BlockingTimer;
};
