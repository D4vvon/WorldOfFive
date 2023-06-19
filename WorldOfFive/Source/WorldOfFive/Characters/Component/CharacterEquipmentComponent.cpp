// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Component/CharacterEquipmentComponent.h"
#include "../WoF_BaseCharacter.h"
#include "../../Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "../../WorldOfFive_Types.h"


// Called when the game starts
void UCharacterEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(GetOwner()->IsA<AWoF_BaseCharacter>(), TEXT("Crush)))))"));
	BaseCharacter = StaticCast<AWoF_BaseCharacter*>(GetOwner());

	CreateLoadout();
}


void UCharacterEquipmentComponent::CreateLoadout()
{
	if (!IsValid(SecondaryWeaponClass))
	{
		return;
	}
	CurrentEquippedWeapon = GetWorld()->SpawnActor<ARangeWeaponItem>(SecondaryWeaponClass);
	CurrentEquippedWeapon->AttachToComponent(BaseCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketCharacterWeapon);
	CurrentEquippedWeapon->SetOwner(BaseCharacter.Get());
}

void UCharacterEquipmentComponent::Fire()
{
	if (IsValid(CurrentEquippedWeapon))
	{
		CurrentEquippedWeapon->FireSetup();
	}
}
