// Fill out your copyright notice in the Description page of Project Settings.


#include "TDTower.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ATDTower::ATDTower()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(RootComponent);
	DetectionSphere->SetCollisionProfileName(TEXT("OverlapAll"));

	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATDTower::OnMonsterEnterRange);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATDTower::OnMonsterExitRange);
	
	Renderer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	Renderer->SetupAttachment(DetectionSphere);
	EffectAreaRenderer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EffectArea"));
	EffectAreaRenderer->SetupAttachment(DetectionSphere);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (CylinderAsset.Succeeded())
	{
		Renderer->SetStaticMesh(CylinderAsset.Object);
		Renderer->SetWorldLocation(FVector(0.0f, 0.0f, 0.0f));
		Renderer->SetWorldScale3D(FVector(1.0f));
		
		EffectAreaRenderer->SetStaticMesh(CylinderAsset.Object);
		EffectAreaRenderer->SetWorldLocation(FVector(0.0f, 0.0f, 0.0f));
		EffectAreaRenderer->SetWorldScale3D(FVector(2.0f, 2.0f, 0.01f));
	}
}

void ATDTower::BeginPlay()
{
	Super::BeginPlay();

	if (BaseMaterial && Renderer)
	{
		DynamicBaseMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		Renderer->SetMaterial(0, DynamicBaseMaterial);
		DynamicBaseMaterial->SetVectorParameterValue(TEXT("Color"), TowerColor);
		DynamicBaseMaterial->SetScalarParameterValue(TEXT("TowerLevel"), TowerLevel);
	}

	if (EffectAreaMaterial && EffectAreaRenderer)
	{
		DynamicEffectAreaMaterial = UMaterialInstanceDynamic::Create(EffectAreaMaterial, this);
		EffectAreaRenderer->SetMaterial(0, DynamicEffectAreaMaterial);
		DynamicEffectAreaMaterial->SetVectorParameterValue(TEXT("Color"), TowerColor);
	}

	MonstersInRange.Reserve(50);
	Effect = FTDEffect(EffectType, EffectInitialValue, bIsTemporaryEffect);
	StartUseEffect();

	float EffectAreaScale = (DetectionSphere->GetScaledSphereRadius() * 2) / 100;
	
	EffectAreaRenderer->SetWorldScale3D(FVector(EffectAreaScale, EffectAreaScale, 0.01f));
}

ETowerType ATDTower::GetTowerType() const
{
	return TowerType;
}

int ATDTower::GetBuyPrice() const
{
	return BuyPrice;
}

int ATDTower::GetUpgradePrice() const
{
	return UpgradePrice;
}

void ATDTower::OnMonsterEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATDMonster* Monster = Cast<ATDMonster>(OtherActor))
	{
		MonstersInRange.Add(Monster);
	}
}

void ATDTower::OnMonsterExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ATDMonster* Monster = Cast<ATDMonster>(OtherActor))
	{
		MonstersInRange.Remove(Monster);
	}
}

void ATDTower::CleanupInvalidMonsters()
{
	MonstersInRange.RemoveAll([](ATDMonster* Monster) {
	   return !IsValid(Monster);
   });
}

void ATDTower::UseEffect()
{
	CleanupInvalidMonsters();
	
	// Default : Apply Effect on Monster in range closest to the core
	if (IsValid(GetClosestToTheCoreMonsterInRange()))
		GetClosestToTheCoreMonsterInRange()->ApplyEffect(Effect);
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

void ATDTower::Upgrade()
{
	++TowerLevel;
	Effect.Upgrade(UpgradeCoeff);
	//UseEffectInterval /= UpgradeCoeff;
	
	DynamicBaseMaterial->SetScalarParameterValue(TEXT("TowerLevel"), TowerLevel);
}

ATDMonster* ATDTower::GetClosestToTheCoreMonsterInRange()
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

ATDMonster* ATDTower::FindNearestMonster(const FVector& InPosition, const float& InDetectionRadius,  const TArray<ATDMonster*>& InExcludedMonsters)
{
	ATDMonster* NearestMonster = nullptr;
	float NearestDistanceSq = FLT_MAX;
    
	// Get all monsters in range at the position
	TArray<AActor*> OverlappingActors;
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		InPosition,
		InDetectionRadius,
		TArray<TEnumAsByte<EObjectTypeQuery>>(),
		ATDMonster::StaticClass(),
		TArray<AActor*>(),
		OverlappingActors
	);
    
	// Get non exlude nearest monster
	for (AActor* Actor : OverlappingActors)
	{
		ATDMonster* Monster = Cast<ATDMonster>(Actor);
		if (Monster && !InExcludedMonsters.Contains(Monster))
		{
			float DistSq = FVector::DistSquared(InPosition, Monster->GetActorLocation());
			if (DistSq < NearestDistanceSq)
			{
				NearestDistanceSq = DistSq;
				NearestMonster = Monster;
			}
		}
	}
    
	return NearestMonster;
}

TArray<ATDMonster*> ATDTower::GetAllMonstersInRange(const FVector& InPosition, const float& InDetectionRadius)
{
	TArray<ATDMonster*> OutMonstersInRange;
	OutMonstersInRange.Reserve(10);

	// Get all monsters in range at the position
	TArray<AActor*> OverlappingActors;
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		InPosition,
		InDetectionRadius,
		TArray<TEnumAsByte<EObjectTypeQuery>>(),
		ATDMonster::StaticClass(),
		TArray<AActor*>(),
		OverlappingActors
	);

	for (AActor* Actor : OverlappingActors)
	{
		ATDMonster* Monster = Cast<ATDMonster>(Actor);
		if (Monster)
		{
			OutMonstersInRange.Add(Monster);
		}
	}

	return OutMonstersInRange;
}
