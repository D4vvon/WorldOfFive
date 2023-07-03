#pragma once

#define ECC_Bullet ECC_GameTraceChannel1
#define  ECC_Melee ECC_GameTraceChannel2

const FName CollisionProfileRagdoll = FName("Ragdoll");
const FName CollisionProfileNoCollision = FName("NoCollision");

const FName SocketCharacterWeapon = FName("CharacterWeaponSocket");

UENUM(BlueprintType)
enum class EEquipmentSlots : uint8
{
	None,
	PrimaryWeapon,
	SecondaryWeapon,
	ThrirdWeapon,
	FourthWeapon,
	MeleeWeapon,
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EWizzardSphereSkillType : uint8
{
	None,
	Missle,
	AOEDamge,
	Casual,
	Field,
	Ray,
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EHitRegistrationType : uint8
{
	HitScan,
	Projectile
};

UENUM(BlueprintType)
enum class EMeleeAttackTypes : uint8
{
	None,
	WeaponAttack,
	MeleeBodyAttack,
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMeleeSkillTypes : uint8
{
	None,
	Defense,
	Buff,
	Attack,
	MAX UMETA(Hidden)
};