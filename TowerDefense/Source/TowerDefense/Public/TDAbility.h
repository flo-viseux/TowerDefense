// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
UCLASS()
class TOWERDEFENSE_API UTDAbility : public UObject
{
	GENERATED_BODY()

public:
	UTDAbility();
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	static UTDAbility* CreateAbility(ETDAbilityType InAbilityType, float InAbilityInitialValue);

	UFUNCTION(BlueprintCallable, Category="Ability")
	void Init(ETDAbilityType InAbilityType, float InAbilityInitialValue);
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	void ApplyEffect(float InEffectValue);

	UFUNCTION(BlueprintCallable, Category="Ability")
	int GetCurrentValue();

private:
	ETDAbilityType AbilityType;

	float AbilityInitialValue;

	float AbilityCurrentValue;
};
