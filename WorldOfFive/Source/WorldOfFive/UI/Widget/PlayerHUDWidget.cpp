// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/PlayerHUDWidget.h"
#include "../../Characters/WoF_BaseCharacter.h"
#include "../../Characters/Component/CharacterAttributesComponent.h"
#include "ReticleWidget.h"
#include "../../../../../../../UE_5.1/Engine/Source/Runtime/UMG/Public/Blueprint/WidgetTree.h"

UReticleWidget* UPlayerHUDWidget::GetReticleWidget()
{
	return WidgetTree->FindWidget<UReticleWidget>(ReticleWidgetName);
}

float UPlayerHUDWidget::GetHealthPercaent() const
{
	float Result = 1.0f;
	APawn* Pawn = GetOwningPlayerPawn();
	AWoF_BaseCharacter* BaseCharacter = Cast<AWoF_BaseCharacter>(Pawn);
	if (IsValid(BaseCharacter))
	{
		const UCharacterAttributesComponent* Attributes = BaseCharacter->GetCharacterAttributesComponent();
		Result = Attributes->GetHealthPercent();
	}
	return Result;
}
