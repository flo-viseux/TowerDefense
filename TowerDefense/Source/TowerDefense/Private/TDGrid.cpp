// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGrid.h"
#include "Kismet/GameplayStatics.h"
#include "TDCell.h"

// Sets default values
ATDGrid::ATDGrid()
{
	PrimaryActorTick.bCanEverTick = false;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ATDGrid::GenerateGrid()
{
    TArray<AActor*> Cells;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATDCell::StaticClass(), Cells);
    for(int i = Cells.Num() - 1; i >= 0; i--)
    {
        if(Cells[i])
        {
            Cells[i]->Destroy();
        }
    }
    
    GridCells.Empty();

    for (int32 X = 0; X < Width; ++X)
    {
        for (int32 Y = 0; Y < Height; ++Y)
        {
            FVector SpawnLocation = GetWorldPositionFromGridPosition(X, Y);
            FActorSpawnParameters SpawnParams;
            FRotator SpawnRotation = FRotator(0, 0, 0);
            ATDCell* newCell = GetWorld()->SpawnActor<ATDCell>(CellBP->GeneratedClass, SpawnLocation, SpawnRotation, SpawnParams);
            newCell->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
            newCell->SetActorLocation(SpawnLocation);
            newCell->X = X;
            newCell->Y = Y;
#if WITH_EDITOR
            newCell->SetActorLabel(FString::Printf(TEXT("Cell_%d_%d"), static_cast<int>(X), static_cast<int>(Y)));
#endif
            newCell->SetActorScale3D(FVector(1, 1, 1));
            GridCells.Add((newCell));
        }
    }

    this->SetActorLocation(FVector((-Width * CellSize - CellSize) / 2, (-Height * CellSize - CellSize) / 2, 0));
}

FVector ATDGrid::GetWorldPositionFromGridPosition(int32 X, int32 Y) const
{
    return GetActorLocation() + FVector(X * CellSize + CellSize, Y * CellSize + CellSize, 0.0f);
}

void ATDGrid::GetGridPositionFromWorldPosition(const FVector& WorldPosition, int32& OutX, int32& OutY) const
{
    FVector LocalPosition = WorldPosition - GetActorLocation();
    OutX = FMath::FloorToInt(LocalPosition.X / CellSize);
    OutY = FMath::FloorToInt(LocalPosition.Y / CellSize);
}

TArray<ATDCell*> ATDGrid::GetGridCells()
{
    return GridCells;
}

ATDCell* ATDGrid::GetGridCell(int32 X, int32 Y) const
{
    for (ATDCell* Cell : GridCells)
    {
        if (Cell->X == X && Cell->Y == Y)
            return Cell;
    }
    
    return nullptr;
}

