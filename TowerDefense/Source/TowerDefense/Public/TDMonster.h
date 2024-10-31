// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDAbility.h"
#include "TDEffect.h"
#include "GameFramework/Pawn.h"
#include "Components/SplineComponent.h"
#include "TDMonster.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDMonster();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Gold")
	int GetGold() const;

	UFUNCTION(BlueprintCallable, Category="Path")
	void SetSplinePath(USplineComponent* NewSpline);
	
	UFUNCTION(BlueprintCallable, Category="Path")
	USplineComponent* GetPath() const;
	
	UFUNCTION(BlueprintCallable, Category="Path")
	float GetDistanceAlongPath() const;

	UFUNCTION(BlueprintCallable, Category="Path")
	void DealDamageAndDestroy();

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyEffect(FTDEffect Effect);

private:
	FTDAbility HealthAbility;
	
	FTDAbility SpeedAbility;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	float InitialHealth;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	float InitialSpeed;

	UPROPERTY(EditAnywhere, Category = "Gold")
	int Gold;

	UPROPERTY()
	USplineComponent* PathToFollow;

	float DistanceAlongPath;
	
	bool bReachedEnd;
};
