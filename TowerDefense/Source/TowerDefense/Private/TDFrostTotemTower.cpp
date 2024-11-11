// Fill out your copyright notice in the Description page of Project Settings.


#include "TDFrostTotemTower.h"

ATDFrostTotemTower::ATDFrostTotemTower()
{
}

void ATDFrostTotemTower::UseEffect()
{
	CleanupInvalidMonsters();
	
	bEffectIsActive = !bEffectIsActive;

	if (bEffectIsActive)
	{
		for (ATDMonster* Monster : MonstersInRange)
		{
			Monster->ApplyEffect(Effect);
		}
	}
	else
	{
		for (ATDMonster* Monster : MonstersInRange)
		{
			Monster->RemoveEffect(Effect);
		}
	}
}

void ATDFrostTotemTower::OnMonsterEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnMonsterEnterRange(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (!bEffectIsActive)
		return;
	
	// Monster Enter Range and effect is active, apply effect
	if (ATDMonster* Monster = Cast<ATDMonster>(OtherActor)) 
		Monster->ApplyEffect(Effect);
}

void ATDFrostTotemTower::OnMonsterExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnMonsterExitRange(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	// Monster Exit Range, remove effect
	if (ATDMonster* Monster = Cast<ATDMonster>(OtherActor)) 
		Monster->RemoveEffect(Effect);
}
