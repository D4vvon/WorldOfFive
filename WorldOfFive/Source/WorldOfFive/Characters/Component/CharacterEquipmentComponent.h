// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterEquipmentComponent.generated.h"

class ARangeWeaponItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WORLDOFFIVE_API UCharacterEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	void Fire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loadout")
	TSubclassOf<ARangeWeaponItem> SecondaryWeaponClass;

private:
	void CreateLoadout();
	
	ARangeWeaponItem* CurrentEquippedWeapon;
	TWeakObjectPtr<class AWoF_BaseCharacter> BaseCharacter;
};
