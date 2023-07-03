// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/Notifies/AnimNotify_SetMeleeHitRegEnable.h"
#include "../../WoF_BaseCharacter.h"
#include "../../../Actors/Equipment/Weapons/MeleeWeaponItem.h"
#include "../../Component/CharacterEquipmentComponent.h"

void UAnimNotify_SetMeleeHitRegEnable::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AWoF_BaseCharacter* CharacterOwner = Cast<AWoF_BaseCharacter>(MeshComp->GetOwner());
	if (!IsValid(CharacterOwner))
	{
		return;
	}
	AMeleeWeaponItem* MeleeWeapon = CharacterOwner->GetCharacterEquipmentComponent()->GetCurrentMeleeWeapon();
	if (IsValid(MeleeWeapon))
	{
		MeleeWeapon->SetIsHitRegEnabled(bIsHitRegEnabled);
	}
}
