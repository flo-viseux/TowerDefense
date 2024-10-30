// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDAbility.h"
#include "TDEffect.h"
#include "GameFramework/Pawn.h"
#include "TDMonster.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDMonster();
	
	UPROPERTY(EditAnywhere, Category = "Health")
	int InitialHealth;

	UPROPERTY(EditAnywhere, Category = "Speed")
	int InitialSpeed;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyEffect(UTDEffect* Effect);

private:
	UTDAbility* HealthAbility;
	
	UTDAbility* SpeedAbility;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
