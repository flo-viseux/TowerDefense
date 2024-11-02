// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDTower.h"
#include "TDTeslaTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDTeslaTower : public ATDTower
{
	GENERATED_BODY()
	
public:
	ATDTeslaTower();
	
protected:
	virtual void UseEffect() override;	
};
