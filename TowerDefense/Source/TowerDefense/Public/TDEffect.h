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
	FTDEffect(): EffectType(ETDEffectType::Hit), EffectValue(0) {}
	
	FTDEffect(ETDEffectType InEffectType, float InEffectValue);

	ETDEffectType GetType() const;

	float GetValue() const;

private:
	ETDEffectType EffectType;

	float EffectValue;
};
