// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDTower.h"
#include "TDGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void InstantiateTower(FVector Location);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "GameMode")
	TSubclassOf<ATDTower> TowerClass;
	
};
