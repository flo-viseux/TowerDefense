// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameModeBase.h"
#include "TDMonster.h"
#include "TDPlayerController.h"
#include "Kismet/GameplayStatics.h"

ATDGameModeBase::ATDGameModeBase(): CurrentSpawner(nullptr)
{
    CurrentWave = 0;
    MonstersSpawnedInWave = 0;
    CurrentSpawnInterval = InitialSpawnInterval;
}

void ATDGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
    // Find Monster Spawner
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATDMonsterSpawner::StaticClass(), FoundActors);
    
    if (FoundActors.Num() > 0)
    {
        CurrentSpawner = Cast<ATDMonsterSpawner>(FoundActors[0]);
    }
    
    StartWave();
}

void ATDGameModeBase::StartWave()
{
    CurrentWave++;
    MonstersSpawnedInWave = 0;
    
    // Decrease spawn interval for difficulty progression
    CurrentSpawnInterval = FMath::Max(
        MinSpawnInterval,
        InitialSpawnInterval - (CurrentWave - 1) * SpawnIntervalDecreaseRate
    );

    // Start spawning monsters
    GetWorld()->GetTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &ATDGameModeBase::SpawnMonster,
        CurrentSpawnInterval,
        true
    );
}

TSubclassOf<ATDMonster> ATDGameModeBase::GetMonsterClassForSpawn()
{
    // If it's time for a boss (every X waves)
    if (CurrentWave % WavesUntilBoss == 0 && MonstersSpawnedInWave == 0)
    {
        return BossMonsterClass;
    }
    
    // Random selection between fast and medium monsters
    float RandomValue = FMath::FRand();
    if (RandomValue < 0.5f) // 50% chance for fast monster
    {
        return FastMonsterClass;
    }
    return MediumMonsterClass; // 50% chance for medium monster
}

void ATDGameModeBase::SpawnMonster()
{
    if (!CurrentSpawner || MonstersSpawnedInWave >= MonstersPerWave)
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        StartWave(); // Start next wave
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // Get spawn location and rotation from the spawner's spline
    FVector SpawnLocation = CurrentSpawner->GetSpawnLocation();
    FRotator SpawnRotation = CurrentSpawner->GetSpawnRotation();

    // Get appropriate monster class
    TSubclassOf<ATDMonster> MonsterClassToSpawn = GetMonsterClassForSpawn();
    
    if (ATDMonster* NewMonster = GetWorld()->SpawnActor<ATDMonster>(
        MonsterClassToSpawn,
        SpawnLocation,
        SpawnRotation,
        SpawnParams))
    {
        NewMonster->SetSplinePath(CurrentSpawner->GetSplinePath());
        MonstersSpawnedInWave++;
    }
}
