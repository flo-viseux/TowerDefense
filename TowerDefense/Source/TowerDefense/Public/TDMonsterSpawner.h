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
	// Sets default values for this actor's properties
	ATDMonsterSpawner();

	// Getter pour la spline (utile pour les ennemis)
	UFUNCTION(BlueprintCallable, Category = "Path")
	USplineComponent* GetPathSpline() const { return PathSpline; }

protected:
	virtual void BeginPlay() override;

	// Composant Spline pour définir le chemin
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Path")
	USplineComponent* PathSpline;

	// Classe de l'ennemi à spawner (doit hériter de Pawn)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<ATDMonster> MonsterClass;

	// Intervalle entre chaque spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = 2.0f;

private:
	// Timer pour gérer le spawn
	FTimerHandle SpawnTimerHandle;

	UFUNCTION()
	void SpawnEnemy();

	// Fonction appelée quand un ennemi est détruit
	UFUNCTION()
	void OnMonsterKilled(AActor* DestroyedActor);
	
	// Fonctions pour contrôler le spawn
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void StopSpawning();
};
