// Fill out your copyright notice in the Description page of Project Settings.


#include "TDTower.h"

ATDTower::ATDTower()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATDTower::BeginPlay()
{
	Super::BeginPlay();

	MonstersInRange.Reserve(50);
	Effect = FTDEffect(EffectType, EffectInitialValue);
	StartUseEffect();
}

void ATDTower::UseEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("UseEffect"));

	/*for (int32 i = MonstersInRange.Num() - 1; i >= 0; --i)
	{
		ATDMonster* Monster = MonstersInRange[i];
        
		if (!IsValid(Monster))
		{
			MonstersInRange.RemoveAt(i);
			continue;
		}
        
		Monster->ApplyEffect(Effect);
	}
	*/

	// Default : Apply Effect on Monster in range closest to the core
	if (IsValid(GetClosestToTheCoreMonster()))
		GetClosestToTheCoreMonster()->ApplyEffect(Effect);
}

void ATDTower::StartUseEffect()
{
	GetWorldTimerManager().SetTimer(
     UseEffectTimerHandle,
     this,
     &ATDTower::UseEffect,
     UseEffectInterval,
     true);
}

void ATDTower::StopUseEffect()
{
    GetWorldTimerManager().ClearTimer(UseEffectTimerHandle);
}

ATDMonster* ATDTower::GetClosestToTheCoreMonster()
{
	ATDMonster* ClosestToTheCoreMonster = nullptr;
	float MaxDistanceAlongSpline = -1.0f;

	for (ATDMonster* Monster : MonstersInRange)
	{
		if (!IsValid(Monster) || !Monster->GetPath())
			continue;

		float CurrentMonsterDistance = Monster->GetDistanceAlongPath();

		if (CurrentMonsterDistance > MaxDistanceAlongSpline)
		{
			MaxDistanceAlongSpline = CurrentMonsterDistance;
			ClosestToTheCoreMonster = Monster;
		}
	}

	return ClosestToTheCoreMonster;
}

