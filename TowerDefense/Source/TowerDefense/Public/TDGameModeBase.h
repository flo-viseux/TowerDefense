// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDMonsterSpawner.h"
#include "TDGameModeBase.generated.h"

class ATDMonster;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATDGameModeBase();

	virtual void BeginPlay() override;
	void StartWave();
	void SpawnMonster();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ATDMonster> FastMonsterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ATDMonster> MediumMonsterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ATDMonster> BossMonsterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float InitialSpawnInterval = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float MinSpawnInterval = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnIntervalDecreaseRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int32 MonstersPerWave = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int32 WavesUntilBoss = 5;

private:
	FTimerHandle SpawnTimerHandle;
	ATDMonsterSpawner* CurrentSpawner;
	float CurrentSpawnInterval;
	int32 CurrentWave;
	int32 MonstersSpawnedInWave;

	TSubclassOf<ATDMonster> GetMonsterClassForSpawn();
};
