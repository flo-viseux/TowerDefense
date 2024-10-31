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
}

float FTDAbility::GetCurrentValue() const
{
	return AbilityCurrentValue;
}


