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

	virtual void OnMonsterEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						   bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnMonsterExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	int ReboundCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float ReboundDetectionRange = 100.0f;
};
