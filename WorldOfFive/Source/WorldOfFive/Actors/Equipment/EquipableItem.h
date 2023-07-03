// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipableItem.generated.h"

class UAnimMontage;
UCLASS(Abstract, NotBlueprintable)
class WORLDOFFIVE_API AEquipableItem : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void SetOwner( AActor* NewOwner ) override;

	FName GetUnEquippedSocketName();
	FName GetEquippedSocketName();

	UAnimMontage* GetCharacterEquipAnimMontage();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipable Item")
	FName UnequippedSocketName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipable Item")
	FName EquippedSocketName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipable Item")
	UAnimMontage* CharacterEqupAnimMontage;

	class AWoF_BaseCharacter* GetCharacterOwner() const;

private:
	TWeakObjectPtr<class AWoF_BaseCharacter> CachedCharacterOwner;
};
