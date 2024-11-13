// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDEffect.generated.h"

UENUM(BlueprintType)
enum class ETDEffectType : uint8
{
	Hit,
	Slow
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct TOWERDEFENSE_API FTDEffect
{
	GENERATED_BODY()
	
public:
	FTDEffect(): EffectType(ETDEffectType::Hit), EffectValue(0), bIsTemporary(false) {}
	
	FTDEffect(ETDEffectType InEffectType, float InEffectValue, bool InIsTemporary);

	ETDEffectType GetType() const;
	
	bool GetIsTemporary() const;

	float GetValue() const;
	
	void Upgrade(float Coeff);

private:
	ETDEffectType EffectType;

	float EffectValue;
	
	bool bIsTemporary;
};
