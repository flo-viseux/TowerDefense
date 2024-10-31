// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDEffect.h"
#include "TDMonster.h"
#include "GameFramework/Actor.h"
#include "TDTower.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDTower : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDTower();

protected:
	virtual void BeginPlay() override;
	
	FTDEffect Effect;

	FTimerHandle UseEffectTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	ETDEffectType EffectType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
    float EffectInitialValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float UseEffectInterval = 2.0f;

	// Array is edited in blueprint, use circle component to know if monsters are in tower's attack range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monsters")
	TArray<ATDMonster*> MonstersInRange;
	
	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual void UseEffect();
	
	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual void StartUseEffect();

	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual void StopUseEffect();

	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual ATDMonster* GetClosestToTheCoreMonster();
};
