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
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCellClickedSignature, FVector, Location);
    
	UPROPERTY(BlueprintAssignable, Category = "Cell")
	FOnCellClickedSignature OnClickedEvent;

	UPROPERTY(EditAnywhere, Category = "Cell")
	int32 X;
	
	UPROPERTY(EditAnywhere, Category = "Cell")
	int32 Y;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Cell")
    void OnCellClicked();
    
    UPROPERTY(EditAnywhere, Category = "Cell")
    bool bIsActive;
};
