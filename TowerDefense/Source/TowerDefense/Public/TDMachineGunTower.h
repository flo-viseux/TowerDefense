// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDTower.h"
#include "TDMachineGunTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDMachineGunTower : public ATDTower
{
	GENERATED_BODY()

public:
	ATDMachineGunTower();
	
protected:
	virtual void UseEffect() override;	
};
