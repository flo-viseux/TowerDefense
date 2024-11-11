// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDCell.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDCell : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDCell();

	UPROPERTY(EditAnywhere, Category = "Cell")
	int32 X;
	
	UPROPERTY(EditAnywhere, Category = "Cell")
	int32 Y;

	UPROPERTY(EditAnywhere, Category = "Cell")
	bool bIsOccuped;
    
	UPROPERTY(EditAnywhere, Category = "Cell")
	bool bIsActive;
	
protected:
	virtual void BeginPlay() override;
};
