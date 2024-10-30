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
UCLASS()
class TOWERDEFENSE_API UTDEffect : public UObject
{
	GENERATED_BODY()
	
public:
	UTDEffect();
	
	UFUNCTION(BlueprintCallable, Category = "Effect")
	static UTDEffect* CreateEffect(ETDEffectType InEffectType, float InEffectValue);
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	void Init(ETDEffectType InEffectType, float InEffectValue);

	UFUNCTION(BlueprintCallable, Category="Effect")
	ETDEffectType GetType();

	UFUNCTION(BlueprintCallable, Category="Effect")
	float GetValue();

private:
	ETDEffectType EffectType;

	float EffectValue;
};
