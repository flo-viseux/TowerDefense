// Fill out your copyright notice in the Description page of Project Settings.


#include "TDAbility.h"

FTDAbility::FTDAbility(ETDAbilityType InAbilityType, float InAbilityInitialValue)
{
	AbilityType = InAbilityType;
	AbilityInitialValue = InAbilityInitialValue;
	AbilityCurrentValue = AbilityInitialValue;
}

void FTDAbility::ApplyEffect(float InEffectValue)
{
	AbilityCurrentValue += InEffectValue;
	AbilityCurrentValue = FMath::Max(0, AbilityCurrentValue);
}

float FTDAbility::GetCurrentValue() const
{
	return AbilityCurrentValue;
}


