// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMonsterSpawner.h"
#include "TDMonster.h"
#include "TDPlayerController.h"
#include "GameFramework/Controller.h"

class ATDPlayerController;

ATDMonsterSpawner::ATDMonsterSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    PathSpline = CreateDefaultSubobject<USplineComponent>(TEXT("PathSpline"));
    RootComponent = PathSpline;
}

void ATDMonsterSpawner::BeginPlay()
{
    StartSpawning();
}

void ATDMonsterSpawner::SpawnEnemy()
{
    // Check spawning's conditions
    if (!MonsterClass || !GetWorld())
    {
        StopSpawning();
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // Set Spawn location and rotation at the beginning of the spline
    FVector SpawnLocation = PathSpline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
    FRotator SpawnRotation = PathSpline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);

    // Spawn Mponster
    ATDMonster* NewMonster = GetWorld()->SpawnActor<ATDMonster>(
        MonsterClass,
        SpawnLocation,
        SpawnRotation,
        SpawnParams
    );

    if (NewMonster)
    {
        // Set monster spline path
        NewMonster->SetSplinePath(PathSpline);
        
        // Add dynamic event to monster destruction
        NewMonster->OnDestroyed.AddDynamic(this, &ATDMonsterSpawner::OnMonsterKilled);
    }
}

void ATDMonsterSpawner::OnMonsterKilled(AActor* DestroyedActor)
{
    // Cast to ATDMonster to get gold value and add it to the player
    if (ATDMonster* MonsterKilled = Cast<ATDMonster>(DestroyedActor))
    {
        int32 GoldToAdd = MonsterKilled->GetGold();

        if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
        {
            if (ATDPlayerController* TDPC = Cast<ATDPlayerController>(PC))
                TDPC->AddGold(GoldToAdd);
        }
    }
}

void ATDMonsterSpawner::StartSpawning()
{
    GetWorldTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &ATDMonsterSpawner::SpawnEnemy,
        SpawnInterval,
        true
    );
}

void ATDMonsterSpawner::StopSpawning()
{
    GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}
