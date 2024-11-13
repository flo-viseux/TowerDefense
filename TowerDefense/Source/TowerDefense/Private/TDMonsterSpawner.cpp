#include "TDMonsterSpawner.h"

ATDMonsterSpawner::ATDMonsterSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    PathSpline = CreateDefaultSubobject<USplineComponent>(TEXT("PathSpline"));
    RootComponent = PathSpline;
}

void ATDMonsterSpawner::BeginPlay()
{
    Super::BeginPlay();
    
    // Spawn the player core at the end of the path
    FVector LastPointLocation = PathSpline->GetLocationAtSplinePoint(
        PathSpline->GetNumberOfSplinePoints() - 1,
        ESplineCoordinateSpace::World
    );
    
    GetWorld()->SpawnActor<AActor>(PlayerCoreClass, LastPointLocation, FRotator::ZeroRotator);
}

FVector ATDMonsterSpawner::GetSpawnLocation() const
{
    return PathSpline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
}

FRotator ATDMonsterSpawner::GetSpawnRotation() const
{
    return PathSpline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);
}
