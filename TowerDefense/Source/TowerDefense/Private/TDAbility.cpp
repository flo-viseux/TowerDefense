// Fill out your copyright notice in the Description page of Project Settings.


#include "TDAbility.h"

UTDAbility::UTDAbility()
{
	// Default
	AbilityType = ETDAbilityType::Health;
	AbilityInitialValue = 0;
	AbilityCurrentValue = AbilityInitialValue;
}

UTDAbility* UTDAbility::CreateAbility(ETDAbilityType InType, float InInitialValue)
{
	UTDAbility* NewAbility = NewObject<UTDAbility>();
	NewAbility->Init(InType, InInitialValue);
	return NewAbility;
}

void UTDAbility::Init(ETDAbilityType InType, float InInitialValue)
{
	AbilityType = InType;
	AbilityInitialValue = InInitialValue;
	AbilityCurrentValue = AbilityInitialValue;
}

void UTDAbility::ApplyEffect(float InEffectValue)
{
	AbilityCurrentValue += InEffectValue;
}

int UTDAbility::GetCurrentValue()
{
	return AbilityCurrentValue;
}
