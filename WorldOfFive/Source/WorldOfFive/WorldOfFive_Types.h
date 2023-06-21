#pragma once

#define ECC_Bullet ECC_GameTraceChannel1

const FName CollisionProfileRagdoll = FName("Ragdoll");

const FName SocketCharacterWeapon = FName("CharacterWeaponSocket");

UENUM(BlueprintType)
enum class EEquipmentSlots : uint8
{
	None,
	PrimaryWeapon,
	SecondaryWeapon,
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