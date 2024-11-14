// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDAbility.generated.h"

UENUM(BlueprintType)
enum class ETDAbilityType : uint8
{
	Health,
	Speed
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct TOWERDEFENSE_API FTDAbility
{
	GENERATED_BODY()

public:
	FTDAbility(): AbilityType(ETDAbilityType::Health), AbilityInitialValue(0), AbilityCurrentValue(0) {}

	FTDAbility(ETDAbilityType InAbilityType, float InAbilityInitialValue);
	
	void ApplyEffect(float InEffectValue);
	void RemoveEffect(float InEffectValue);

	float GetCurrentValue() const;

private:
	ETDAbilityType AbilityType;

	float AbilityInitialValue;

	float AbilityCurrentValue;
};
