// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDTower.h"
#include "TDFrostTotemTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDFrostTotemTower : public ATDTower
{
	GENERATED_BODY()
	
public:
	ATDFrostTotemTower();
	
protected:
	virtual void UseEffect() override;	
};
