// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDTower.h"
#include "TDGrenadeLauncherTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDGrenadeLauncherTower : public ATDTower
{
	GENERATED_BODY()
	
public:
	ATDGrenadeLauncherTower();
	
protected:
	virtual void UseEffect() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float GrenadeExplosionRadius = 50;
};
