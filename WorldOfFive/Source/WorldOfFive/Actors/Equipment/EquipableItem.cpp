// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/EquipableItem.h"
#include "Characters/WoF_BaseCharacter.h"


void AEquipableItem::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	if (IsValid(NewOwner))
	{
		CachedCharacterOwner = StaticCast<AWoF_BaseCharacter*>(GetOwner());
	}
	else
	{
		CachedCharacterOwner = nullptr;
	}
}

FName AEquipableItem::GetUnEquippedSocketName()
{
	return UnequippedSocketName;
}

FName AEquipableItem::GetEquippedSocketName()
{
	return EquippedSocketName;
}

UAnimMontage* AEquipableItem::GetCharacterEquipAnimMontage()
{
	return CharacterEqupAnimMontage;
}

AWoF_BaseCharacter* AEquipableItem::GetCharacterOwner() const
{
	return CachedCharacterOwner.IsValid() ? CachedCharacterOwner.Get() : nullptr;
}
