// Fill out your copyright notice in the Description page of Project Settings.


#include "TDEffect.h"

UTDEffect::UTDEffect()
{
	// Default
	EffectType = ETDEffectType::Hit;
	EffectValue = 0;
}

UTDEffect* UTDEffect::CreateEffect(ETDEffectType InEffectType, float InEffectValue)
{
	UTDEffect* NewEffect = NewObject<UTDEffect>();
	NewEffect->Init(InEffectType, InEffectValue);
	return NewEffect;
}

void UTDEffect::Init(ETDEffectType InEffectType, float InEffectValue)
{
	EffectType = InEffectType;
	EffectValue = InEffectValue;
}

ETDEffectType UTDEffect::GetType()
{
	return EffectType;
}

float UTDEffect::GetValue()
{
	return EffectValue;
}
