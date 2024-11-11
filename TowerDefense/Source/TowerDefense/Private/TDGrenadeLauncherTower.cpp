// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGrenadeLauncherTower.h"

ATDGrenadeLauncherTower::ATDGrenadeLauncherTower()
{
	
}

void ATDGrenadeLauncherTower::UseEffect()
{
	CleanupInvalidMonsters();
	
	ATDMonster* ClosestMonster = GetClosestToTheCoreMonsterInRange();
	if (!IsValid(ClosestMonster))
		return;

	FVector GrenadeExplosionLocation = ClosestMonster->GetActorLocation();
	
	for (ATDMonster* Monster : GetAllMonstersInRange(GrenadeExplosionLocation, GrenadeExplosionRadius))
	{
		if (IsValid(Monster))
			Monster->ApplyEffect(Effect);
	}
}
