// Fill out your copyright notice in the Description page of Project Settings.


#include "TDEffect.h"

FTDEffect::FTDEffect(ETDEffectType InEffectType, float InEffectValue, bool InIsTemporary = false)
{
	EffectType = InEffectType;
	EffectValue = InEffectValue;
	bIsTemporary = InIsTemporary;
}

ETDEffectType FTDEffect::GetType() const
{
	return EffectType;
}

bool FTDEffect::GetIsTemporary() const
{
	return bIsTemporary;
}

void FTDEffect::Upgrade(float Coeff)
{
	EffectValue *= Coeff;
}

float FTDEffect::GetValue() const
{
	return EffectValue;
}


