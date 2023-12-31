// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetMeleeHitRegEnable.generated.h"

/**
 * 
 */
UCLASS()
class WORLDOFFIVE_API UAnimNotify_SetMeleeHitRegEnable : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MeleeHitReg")
	bool bIsHitRegEnabled;
	
};
