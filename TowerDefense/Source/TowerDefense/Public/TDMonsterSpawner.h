// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDMonster.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Components/SplineComponent.h"
#include "TDMonsterSpawner.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	ATDMonsterSpawner();

	FVector GetSpawnLocation() const;
	FRotator GetSpawnRotation() const;
	USplineComponent* GetSplinePath() const { return PathSpline; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USplineComponent* PathSpline;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> PlayerCoreClass;
};

