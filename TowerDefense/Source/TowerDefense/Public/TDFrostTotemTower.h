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
	bool bEffectIsActive = false;
	
	virtual void UseEffect() override;

	virtual void OnMonsterEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						   bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnMonsterExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
