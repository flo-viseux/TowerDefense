// Fill out your copyright notice in the Description page of Project Settings.


#include "TDEffect.h"

FTDEffect::FTDEffect(ETDEffectType InEffectType, float InEffectValue)
{
	EffectType = InEffectType;
	EffectValue = InEffectValue;
}

ETDEffectType FTDEffect::GetType() const
{
	return EffectType;
}

float FTDEffect::GetValue() const
{
	return EffectValue;
}


