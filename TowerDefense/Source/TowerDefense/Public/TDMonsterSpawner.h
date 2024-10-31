// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDMonster.h"
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

	// Getter for the spline useful for monsters
	UFUNCTION(BlueprintCallable, Category = "Path")
	USplineComponent* GetPathSpline() const { return PathSpline; }

protected:
	virtual void BeginPlay() override;

	// Spline Component to define path
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Path")
	USplineComponent* PathSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<ATDMonster> MonsterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = 2.0f;

private:
	FTimerHandle SpawnTimerHandle;

	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void OnMonsterKilled(AActor* DestroyedActor);
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void StopSpawning();
};
