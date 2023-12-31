// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldOfFive_Types.h"
#include "CharacterEquipmentComponent.generated.h"

typedef TArray<class AEquipableItem*, TInlineAllocator<(uint32)EEquipmentSlots::MAX>> TItemsArray;

class ARangeWeaponItem;
class AMeleeWeaponItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WORLDOFFIVE_API UCharacterEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	void EquipItemInSlot(EEquipmentSlots Slot);

	void AttachCurrentItemToEquipmentSocket();

	void UnequipCurrentItem();

	void EquipPreimaryItem();
	void EquipSecondaryItem();
	void EquipThirthItem();
	void EquipFourthItem();
	bool IsEquipping();
	bool IsEquip();

	void EquipMeleeItem();


	ARangeWeaponItem* GetCurrentRangeWeapon();
	AMeleeWeaponItem* GetCurrentMeleeWeapon() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loadout")
	TMap<EEquipmentSlots, TSubclassOf<class AEquipableItem>> ItemsLoadout;

private:
	void CreateLoadout();
	TItemsArray ItemsArray;

	EEquipmentSlots CurrentEquippedSlot;
	class AEquipableItem* CurrentEquippedItem;

	class AMeleeWeaponItem* CurrentMeleeWeaponItem;

	bool bIsEquip = false;
	bool bIsEquiping = false;
	FTimerHandle EquipTimer;
		
	ARangeWeaponItem* CurrentEquippedWeapon;
	TWeakObjectPtr<class AWoF_BaseCharacter> BaseCharacter;
};
