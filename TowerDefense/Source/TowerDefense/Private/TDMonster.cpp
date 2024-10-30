// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMonster.h"

// Sets default values
ATDMonster::ATDMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATDMonster::ApplyEffect(UTDEffect* Effect)
{
	switch (Effect->GetType())
	{
		case ETDEffectType::Hit:
			HealthAbility->ApplyEffect(Effect->GetValue());
			break;
		case ETDEffectType::Slow:
			SpeedAbility->ApplyEffect(Effect->GetValue());
			break;
	}
}

// Called when the game starts or when spawned
void ATDMonster::BeginPlay()
{
	Super::BeginPlay();

	HealthAbility = UTDAbility::CreateAbility(ETDAbilityType::Health, InitialHealth);
	SpeedAbility = UTDAbility::CreateAbility(ETDAbilityType::Speed, InitialSpeed);
}

// Called every frame
void ATDMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

