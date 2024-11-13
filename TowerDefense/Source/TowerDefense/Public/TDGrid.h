// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDGrid.generated.h"

class ATDCell;

UCLASS()
class TOWERDEFENSE_API ATDGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDGrid();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FVector GetWorldPositionFromGridPosition(int32 X, int32 Y) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void GetGridPositionFromWorldPosition(const FVector& WorldPosition, int32& OutX, int32& OutY) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	TArray<ATDCell*> GetGridCells();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	ATDCell* GetGridCell(int32 X, int32 Y) const;

protected:
	UFUNCTION(CallInEditor, Category = "Grid")
	void GenerateGrid();
	
	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 Width = 10;

	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 Height = 10;

	UPROPERTY(EditAnywhere, Category = "Grid")
	float CellSize = 100.0f;
	
	UPROPERTY(EditAnywhere, Category = "Grid")
	UBlueprint* CellBP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<ATDCell*> GridCells;
};
