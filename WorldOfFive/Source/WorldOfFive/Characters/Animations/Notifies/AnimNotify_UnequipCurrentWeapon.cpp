// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/Notifies/AnimNotify_UnequipCurrentWeapon.h"
#include "../../WoF_BaseCharacter.h"
#include "../../Component/CharacterEquipmentComponent.h"

void UAnimNotify_UnequipCurrentWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
}
