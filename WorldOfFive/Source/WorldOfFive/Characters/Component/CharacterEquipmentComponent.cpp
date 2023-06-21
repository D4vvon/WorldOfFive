// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Component/CharacterEquipmentComponent.h"
#include "../WoF_BaseCharacter.h"
#include "../../Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "../../WorldOfFive_Types.h"
#include "Actors/Equipment/EquipableItem.h"


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

	UnequipCurrentItem();
	CurrentEquippedItem = ItemsArray[(uint32)Slot];
	CurrentEquippedWeapon = Cast<ARangeWeaponItem>(CurrentEquippedItem);

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
	}
	if (IsValid(CurrentEquippedWeapon))
	{
		CurrentEquippedWeapon->StopFire();
	}
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

bool UCharacterEquipmentComponent::IsEquipping()
{
	return bIsEquiping;
}

ARangeWeaponItem* UCharacterEquipmentComponent::GetCurrentRangeWeapon()
{
	return CurrentEquippedWeapon;
}
