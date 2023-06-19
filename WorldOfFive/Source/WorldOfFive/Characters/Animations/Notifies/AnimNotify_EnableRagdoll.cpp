// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/Notifies/AnimNotify_EnableRagdoll.h"
#include "WorldOfFive_Types.h"

void UAnimNotify_EnableRagdoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName(CollisionProfileRagdoll);
}
