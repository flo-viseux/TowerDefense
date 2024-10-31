// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameModeBase.h"

#include "TDCell.h"
#include "TDGrid.h"
#include "TDTower.h"
#include "Kismet/GameplayStatics.h"

void ATDGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ATDGrid* Grid = Cast<ATDGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), ATDGrid::StaticClass()));
	if (Grid)
	{
		for (ATDCell* Cell : Grid->GetGridCells())
			Cell->OnClickedEvent.AddDynamic(this, &ATDGameModeBase::InstantiateTower);
	}
}

void ATDGameModeBase::InstantiateTower(FVector Location)
{
	if (TowerClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<ATDTower>(TowerClass, Location, FRotator::ZeroRotator, SpawnParams);
	}
}


