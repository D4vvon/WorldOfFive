// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class WORLDOFFIVE_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UReticleWidget* GetReticleWidget();

protected:
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;
	
	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent() const;

	UFUNCTION(BlueprintCallable)
	float GetManaPercent() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget names")
	FName ReticleWidgetName;
	
};
