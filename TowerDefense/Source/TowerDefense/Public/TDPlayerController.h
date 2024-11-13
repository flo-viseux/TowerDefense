// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDCell.h"
#include "GameFramework/PlayerController.h"
#include "TDGameModeBase.h"
#include "TDGrid.h"
#include "TDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChanged, int32, NewGold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectedTowerChanged, bool, NotNull, int, NewUpgradePrice);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnInitTowersPrice, int, MachineGunTowerPrice, int, FrostTotemTowerPrice, int, GrenadeLauncherTowerPrice, int, TeslaTowerPrice);

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
	
	UFUNCTION(BlueprintCallable, Category="Gold")
	void RemoveGold(int GoldToRemove);

	UFUNCTION(BlueprintCallable, Category="Life")
	int GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category="Life")
	void RemoveHealth(int HealthToRemove);
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGoldChanged OnGoldChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSelectedTowerChanged OnSelectedTowerChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInitTowersPrice OnInitTowersPrice;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ClickAction;

	// Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DefaultValue")
	int InitialGold = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DefaultValue")
	int InitialHealth = 100;
	
	UPROPERTY(BlueprintReadWrite, Category = "Tower")
	ETowerType CurrentTowerTypeSelected;

	UPROPERTY(BlueprintReadWrite, Category = "Tower")
	ATDTower* CurrentSelectedTower;
	
	UPROPERTY(EditDefaultsOnly, Category = "TowerClasses")
	TSubclassOf<ATDTower> MachineGunTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "TowerClasses")
	TSubclassOf<ATDTower> FrostTotemTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "TowerClasses")
	TSubclassOf<ATDTower> GrenadeLauncherTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "TowerClasses")
	TSubclassOf<ATDTower> TeslaTowerClass;
	
private:
	int Gold;
	
	FTDAbility HealthAbility;

	ATDGrid* Grid;

	void OnClick();

	UFUNCTION(BlueprintCallable, Category="MouseEvent")
	ATDCell* GetCellUnderMouse();
	
	UFUNCTION(BlueprintCallable, Category="MouseEvent")
	ATDTower* GetTowerUnderMouse();

	UFUNCTION(BlueprintCallable, Category = "Tower")
	TSubclassOf<ATDTower> GetTowerClassFromType(ETowerType TowerType) const;
	
	UFUNCTION(BlueprintCallable, Category = "Tower")
	void DestroyTower();

	UFUNCTION(BlueprintCallable, Category="Tower")
	void UpgradeTower();
};
