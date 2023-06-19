// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/WoF_BaseCharacterAnimInstance.h"
#include "../WoF_BaseCharacter.h"
#include "../Component/WoF_BaseCharacterMovementComp.h"

void UWoF_BaseCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(TryGetPawnOwner()->IsA<AWoF_BaseCharacter>(), TEXT("Crush)"));
	BaseCharacter = StaticCast<AWoF_BaseCharacter*>(TryGetPawnOwner());
}

void UWoF_BaseCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!BaseCharacter.IsValid())
	{
		return;
	}

	UWoF_BaseCharacterMovementComp* CharacterMovement = BaseCharacter->GetBaseCharacterMovementComponent();

	Speed = CharacterMovement->Velocity.Size();
	bIsFalling = CharacterMovement->IsFalling();
	bIsCrouching = CharacterMovement->IsCrouching();
	bIsSprinting = CharacterMovement->IsSprinting();
	bIsStrafing = !CharacterMovement->bOrientRotationToMovement;

	Direction = CalculateDirection(CharacterMovement->Velocity, BaseCharacter->GetActorRotation());

}
