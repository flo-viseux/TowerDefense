// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDEffect.h"
#include "TDMonster.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "TDTower.generated.h"

UENUM(BlueprintType)
enum class ETowerType : uint8
{
	MachineGun    UMETA(DisplayName = "MachineGun"),
	FrostTotem       UMETA(DisplayName = "FrostTotem"),
	Tesla       UMETA(DisplayName = "Tesla"),
	GrenadeLauncher     UMETA(DisplayName = "GrenadeLauncher")
};

UCLASS()
class TOWERDEFENSE_API ATDTower : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDTower();

	ETowerType GetTowerType();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tower|Type")
	ETowerType TowerType;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
    
	UPROPERTY(EditDefaultsOnly, Category = "Tower|Appearance")
	FLinearColor TowerColor = FLinearColor::White;
    
	UPROPERTY(EditDefaultsOnly, Category = "Tower|Appearance")
	float TowerLevel = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Tower|Appearance")
	UMaterialInterface* BaseMaterial;
	
	FTDEffect Effect;

	FTimerHandle UseEffectTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	ETDEffectType EffectType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
    float EffectInitialValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float UseEffectInterval = 2.0f;

	UPROPERTY(VisibleAnywhere, Category = "Renderer")
	UStaticMeshComponent* Renderer;
	
	UPROPERTY(VisibleAnywhere, Category = "Detection")
	USphereComponent* DetectionSphere;

	UFUNCTION()
	virtual void OnMonsterEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						   bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnMonsterExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Array is edited in blueprint, use circle component to know if monsters are in tower's attack range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monsters")
	TArray<ATDMonster*> MonstersInRange;

	
	void CleanupInvalidMonsters();
	
	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual void UseEffect();
	
	UFUNCTION(BlueprintCallable, Category = "Effect")
	void StartUseEffect();

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void StopUseEffect();

	static const FName BeamStartParam;
	static const FName BeamEndParam;
	static const FName BeamLengthParam;

	UPROPERTY(EditAnywhere, Category = "Effect|VFX")
	UNiagaraSystem* NiagaraSystem;
	
	UFUNCTION(BlueprintCallable, Category = "Effect")
	virtual void SpawnVFX(const FVector& StartLocation, const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Monster")
	ATDMonster* GetClosestToTheCoreMonsterInRange();

	UFUNCTION(BlueprintCallable, Category = "Monster")
	ATDMonster* FindNearestMonster(const FVector& InPosition, const float& InDetectionRadius, const TArray<ATDMonster*>& InExcludedMonsters);
	
	UFUNCTION(BlueprintCallable, Category = "Monster")
	TArray<ATDMonster*> GetAllMonstersInRange(const FVector& InPosition, const float& InDetectionRadius);
};
