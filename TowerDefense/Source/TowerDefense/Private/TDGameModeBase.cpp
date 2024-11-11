// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameModeBase.h"
#include "TDTower.h"

void ATDGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}


void ATDGameModeBase::InstantiateTower(TSubclassOf<ATDTower> TowerClass, FVector SpawnLocation)
{
	if (TowerClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<ATDTower>(TowerClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}
}
