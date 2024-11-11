// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDCell.h"
#include "GameFramework/PlayerController.h"
#include "TDGameModeBase.h"
#include "TDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ATDPlayerController();
	
    virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintCallable, Category="Gold")
	int GetGold() const;

	UFUNCTION(BlueprintCallable, Category="Gold")
	void AddGold(int GoldToAdd);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gold")
	int InitialGold;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ClickAction;

	// Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(BlueprintReadWrite, Category = "Tower")
	ETowerType CurrentTowerType;

	UFUNCTION(BlueprintCallable, Category = "Tower")
	void SetCurrentTowerType(ETowerType NewType)
	{
		CurrentTowerType = NewType;
	}
	
	UPROPERTY(EditDefaultsOnly, Category = "Tower Classes")
	TSubclassOf<ATDTower> MachineGunTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Classes")
	TSubclassOf<ATDTower> FrostTotemTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Classes")
	TSubclassOf<ATDTower> GrenadeLauncherTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Classes")
	TSubclassOf<ATDTower> TeslaTowerClass;
	
private:
	UPROPERTY()
	ATDGameModeBase* GameMode;
	
	int Gold;

	UFUNCTION(BlueprintCallable, Category="MouseEvent")
	ATDCell* GetCellUnderMouse();

	void OnClick();

	UFUNCTION(BlueprintCallable, Category = "Tower")
	TSubclassOf<ATDTower> GetTowerClassFromType(ETowerType TowerType) const
	{
		switch (TowerType)
		{
		case ETowerType::MachineGun:
			return MachineGunTowerClass;
		case ETowerType::FrostTotem:
			return FrostTotemTowerClass;
		case ETowerType::GrenadeLauncher:
			return GrenadeLauncherTowerClass;
		case ETowerType::Tesla:
			return TeslaTowerClass;
		default:
			return nullptr;
		}
	}
};
