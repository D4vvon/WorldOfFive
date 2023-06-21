// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/EquipableItem.h"


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
