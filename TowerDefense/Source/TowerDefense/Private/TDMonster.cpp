// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMonster.h"

// Sets default values
ATDMonster::ATDMonster()
{
	PrimaryActorTick.bCanEverTick = true;
    
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	RootComponent = MeshComponent;
    
	DistanceAlongSpline = 0.0f;
	bReachedEnd = false;
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

void ATDMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PathToFollow || bReachedEnd)
		return;

	// Move and rotate the monster along the spline
	DistanceAlongSpline += SpeedAbility->GetCurrentValue() * DeltaTime;
    
	FVector NewLocation = PathToFollow->GetLocationAtDistanceAlongSpline(
		DistanceAlongSpline, 
		ESplineCoordinateSpace::World
	);
    
	FRotator NewRotation = PathToFollow->GetRotationAtDistanceAlongSpline(
		DistanceAlongSpline, 
		ESplineCoordinateSpace::World
	);

	SetActorLocationAndRotation(NewLocation, NewRotation);

	// Check if monster reached the end of the spline
	if (DistanceAlongSpline >= PathToFollow->GetSplineLength())
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

void ATDMonster::DealDamageAndDestroy()
{
	// TODO : apply damage to player core
    
	Destroy();
}

int ATDMonster::GetGold() const
{
	return Gold;
}

