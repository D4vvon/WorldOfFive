// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Component/CharacterEquipmentComponent.h"
#include "../WoF_BaseCharacter.h"
#include "../../Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "../../WorldOfFive_Types.h"
#include "Actors/Equipment/EquipableItem.h"
#include "Actors/Equipment/Weapons/MeleeWeaponItem.h"
#include "WoF_BaseCharacterMovementComp.h"


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
	ItemsArray.AddZeroed((uint32)EEquipmentSlots::MAX);
	for (const TPair<EEquipmentSlots, TSubclassOf<AEquipableItem>>& ItemPair : ItemsLoadout)
	{
		if (!IsValid(ItemPair.Value))
		{
			continue;
		}
		AEquipableItem* Item = GetWorld()->SpawnActor<AEquipableItem>(ItemPair.Value);
		Item->AttachToComponent(BaseCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, Item->GetUnEquippedSocketName());
		Item->SetOwner(BaseCharacter.Get());
		ItemsArray[(uint32)ItemPair.Key] = Item;
	}

/*
	CurrentEquippedWeapon = GetWorld()->SpawnActor<ARangeWeaponItem>(SecondaryWeaponClass);
	CurrentEquippedWeapon->AttachToComponent(BaseCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketCharacterWeapon);
	CurrentEquippedWeapon->SetOwner(BaseCharacter.Get());*/
}

void UCharacterEquipmentComponent::EquipItemInSlot(EEquipmentSlots Slot)
{
	if (bIsEquiping)
	{
		return;
	}
	if (CurrentEquippedSlot != EEquipmentSlots::None)
	{
		UnequipCurrentItem();
	}
	CurrentEquippedItem = ItemsArray[(uint32)Slot];
	CurrentEquippedWeapon = Cast<ARangeWeaponItem>(CurrentEquippedItem);
	CurrentMeleeWeaponItem = Cast<AMeleeWeaponItem>(CurrentEquippedItem);

	if (IsValid(CurrentEquippedItem))
	{
		UAnimMontage* EquipingMontage = CurrentEquippedItem->GetCharacterEquipAnimMontage();
		if (IsValid(EquipingMontage))
		{
			bIsEquiping = true;
			float EquipDuretion = BaseCharacter->PlayAnimMontage(EquipingMontage);
			GetWorld()->GetTimerManager().SetTimer(EquipTimer, this, &UCharacterEquipmentComponent::AttachCurrentItemToEquipmentSocket, EquipDuretion, false);
		}
		else
		{
			AttachCurrentItemToEquipmentSocket();
		}
		CurrentEquippedSlot = Slot;
	}
	else
	{
		CurrentEquippedSlot = EEquipmentSlots::None;
	}
}

void UCharacterEquipmentComponent::AttachCurrentItemToEquipmentSocket()
{
	CurrentEquippedItem->AttachToComponent(BaseCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, CurrentEquippedItem->GetEquippedSocketName());
	bIsEquiping = false;
}

void UCharacterEquipmentComponent::UnequipCurrentItem()
{
	if (IsValid(CurrentEquippedItem))
	{
		CurrentEquippedItem->AttachToComponent(BaseCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, CurrentEquippedItem->GetUnEquippedSocketName());
		bIsEquip = false;
	}
	if (IsValid(CurrentEquippedWeapon))
	{
		CurrentEquippedWeapon->StopFire();
	}
	CurrentEquippedWeapon = nullptr;
	CurrentEquippedItem = nullptr;
	CurrentEquippedItem = nullptr;
	CurrentMeleeWeaponItem = nullptr;
	CurrentEquippedSlot = EEquipmentSlots::None;
}

void UCharacterEquipmentComponent::EquipPreimaryItem()
{
	if (CurrentEquippedSlot != EEquipmentSlots::PrimaryWeapon)
	{
		EquipItemInSlot(EEquipmentSlots::PrimaryWeapon);
	}
}

void UCharacterEquipmentComponent::EquipSecondaryItem()
{
	if (CurrentEquippedSlot != EEquipmentSlots::SecondaryWeapon)
	{
		EquipItemInSlot(EEquipmentSlots::SecondaryWeapon);
	}
}

void UCharacterEquipmentComponent::EquipThirthItem()
{
	if (CurrentEquippedSlot != EEquipmentSlots::ThrirdWeapon)
	{
		EquipItemInSlot(EEquipmentSlots::ThrirdWeapon);
	}
}

void UCharacterEquipmentComponent::EquipFourthItem()
{
	if (CurrentEquippedSlot != EEquipmentSlots::FourthWeapon)
	{
		EquipItemInSlot(EEquipmentSlots::FourthWeapon);
	}
}

bool UCharacterEquipmentComponent::IsEquipping()
{
	return bIsEquiping;
}

bool UCharacterEquipmentComponent::IsEquip()
{
	return bIsEquip;
}

void UCharacterEquipmentComponent::EquipMeleeItem()
{
	if (CurrentEquippedSlot != EEquipmentSlots::MeleeWeapon)
	{
		EquipItemInSlot(EEquipmentSlots::MeleeWeapon);
		bIsEquip = true;
	}
}

ARangeWeaponItem* UCharacterEquipmentComponent::GetCurrentRangeWeapon()
{
	return CurrentEquippedWeapon;
}

class AMeleeWeaponItem* UCharacterEquipmentComponent::GetCurrentMeleeWeapon() const
{
	return CurrentMeleeWeaponItem;
}
