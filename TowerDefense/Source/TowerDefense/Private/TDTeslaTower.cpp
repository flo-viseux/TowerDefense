// Fill out your copyright notice in the Description page of Project Settings.


#include "TDTeslaTower.h"

ATDTeslaTower::ATDTeslaTower()
{
}

void ATDTeslaTower::UseEffect()
{
	CleanupInvalidMonsters();
	
	TArray<ATDMonster*> HitMonsters;
	
	ATDMonster* FirstTarget = GetClosestToTheCoreMonsterInRange();

	if (!IsValid(FirstTarget))
		return;

	FirstTarget->ApplyEffect(Effect);
	HitMonsters.Add(FirstTarget);

	FVector CurrentPosition = FirstTarget->GetActorLocation();
	
	for (int i = 0; i < ReboundCount; ++i)
	{
		if (ATDMonster* NextTarget = FindNearestMonster(CurrentPosition, ReboundDetectionRange, HitMonsters))
		{
			NextTarget->ApplyEffect(Effect);
            
			SpawnVFX(CurrentPosition, NextTarget->GetActorLocation());
            
			CurrentPosition = NextTarget->GetActorLocation();
            
			HitMonsters.Add(NextTarget);
		}
		else
		{
			break;
		}
	}
}

void ATDTeslaTower::OnMonsterEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnMonsterEnterRange(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UE_LOG(LogTemp, Display, TEXT("OnMonsterEnterRange"));
}

void ATDTeslaTower::OnMonsterExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnMonsterExitRange(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	UE_LOG(LogTemp, Display, TEXT("OnMonsterExitRange"));
}
