// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Equipment/EquipableItem.h"
#include "WorldOfFive_Types.h"
#include "RangeWeaponItem.generated.h"

UENUM(BlueprintType)
enum class EWeaponFireMode : uint8
{
	Single,
	Auto
};

//SkillParameters struct
USTRUCT(BlueprintType)
struct FSkillParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillParams")
	class UAnimMontage* CharacterCastingAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillParams")
	class UTexture2D* SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillParams")
	float CooldownDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillParams")
	EWizzardSphereSkillType SkillType = EWizzardSphereSkillType::Missle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillParams", meta = (EditCondition = "1 == 0"))
	EHitRegistrationType HitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillParams")
	class UNiagaraSystem* ResultVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillParams")
	float ManaConsumption = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillParams")
	float SkillDelay = 2.0f;

	FTimerHandle CooldownTimer;

};

typedef TArray<FSkillParameters, TInlineAllocator<(uint32)EWizzardSphereSkillType::MAX>> TSkillsArray;

class UAnimMontage;
UCLASS(Blueprintable)
class WORLDOFFIVE_API ARangeWeaponItem : public AEquipableItem
{
	GENERATED_BODY()
	
public:
	ARangeWeaponItem();

	void FireSetup();
	void StartFire();
	void Fire();
	void StopFire();

	void NextSkill();
	void PreviousSkill();
	void SetSkillToWeapon(EWizzardSphereSkillType Skill);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UWeaponBarellComponent* WeaponBarell;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	//UAnimMontage* CharacterFireMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	UAnimMontage* WeaponAnimMontage;

	//rounds per minute
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon params", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float RateOfFire = 10.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon params")
	EWeaponFireMode WeaponFireMode = EWeaponFireMode::Single;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills")
	TMap<EWizzardSphereSkillType, FSkillParameters> SkillsMap;

private:
	void CreateSkillsLoadout();

	float PlayAnimMontage(UAnimMontage* AnimMontage);

	FTimerHandle SpellTimer;

	float GetShotTimerInterval();
	FTimerHandle ShotTimer;

	TSkillsArray SkillsArray;
	EWizzardSphereSkillType CurrentSkillType;
	FSkillParameters CurrentSkillParams;

	uint32 NextSkillsArrayIndex(uint32 CurrentIndex);
	uint32 PreviousSkillsArrayIndex(uint32 CurrentIndex);
};
