// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMonster.h"

#include "Components/TimelineComponent.h"

// Sets default values
ATDMonster::ATDMonster()
{
	PrimaryActorTick.bCanEverTick = true;
    
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	RootComponent = MeshComponent;
    
	DistanceAlongPath = 0.0f;
	bReachedEnd = false;
}

void ATDMonster::BeginPlay()
{
	Super::BeginPlay();

	HealthAbility = FTDAbility(ETDAbilityType::Health, InitialHealth);
	SpeedAbility = FTDAbility(ETDAbilityType::Speed, InitialSpeed);
}

void ATDMonster::ApplyEffect(FTDEffect Effect)
{
	UE_LOG(LogTemp, Warning, TEXT("Effect Value : %f"), Effect.GetValue());
	
	switch (Effect.GetType())
	{
		case ETDEffectType::Hit:
			HealthAbility.ApplyEffect(Effect.GetValue());
		
			if (HealthAbility.GetCurrentValue() <= 0)
				this->Destroy();
				
			break;
		case ETDEffectType::Slow:
			SpeedAbility.ApplyEffect(Effect.GetValue());
			break;
	}
}

void ATDMonster::RemoveEffect(FTDEffect Effect)
{
	// Proto
	switch (Effect.GetType())
	{
		case ETDEffectType::Hit:
			HealthAbility.ApplyEffect(-Effect.GetValue());
			break;
		case ETDEffectType::Slow:
			SpeedAbility.ApplyEffect(-Effect.GetValue());
			break;
	}
}

void ATDMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PathToFollow || bReachedEnd)
		return;

	// Move and rotate the monster along the spline
	DistanceAlongPath += SpeedAbility.GetCurrentValue() * DeltaTime;
    
	FVector NewLocation = PathToFollow->GetLocationAtDistanceAlongSpline(
		DistanceAlongPath, 
		ESplineCoordinateSpace::World
	);
    
	FRotator NewRotation = PathToFollow->GetRotationAtDistanceAlongSpline(
		DistanceAlongPath, 
		ESplineCoordinateSpace::World
	);

	SetActorLocationAndRotation(NewLocation, NewRotation);

	// Check if monster reached the end of the spline
	if (DistanceAlongPath >= PathToFollow->GetSplineLength())
	{
		bReachedEnd = true;
		DealDamageAndDestroy();
	}
}

void ATDMonster::SetSplinePath(USplineComponent* NewSpline)
{
	PathToFollow = NewSpline;
    
	// Place monster at the beginning of the spline
	if (PathToFollow)
	{
		SetActorLocation(PathToFollow->GetLocationAtDistanceAlongSpline(
			0.0f, 
			ESplineCoordinateSpace::World
		));
	}
}

USplineComponent* ATDMonster::GetPath() const
{
	return PathToFollow;
}

float ATDMonster::GetDistanceAlongPath() const
{
	return DistanceAlongPath;
}

void ATDMonster::DealDamageAndDestroy()
{
	// TODO : apply damage to player core
    
	Destroy();
}

int ATDMonster::GetGold() const
{
	return Gold;
}

