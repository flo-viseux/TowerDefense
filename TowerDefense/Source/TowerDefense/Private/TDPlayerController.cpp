// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TDTower.h"


ATDPlayerController::ATDPlayerController(): ClickAction(nullptr), DefaultMappingContext(nullptr),
											InitialGold(0), Gold(0), Grid(nullptr), InitialHealth(0),
											CurrentTowerTypeSelected(), CurrentSelectedTower(nullptr)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ATDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &ATDPlayerController::OnClick);
	}
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetPawn()->SetActorLocation(FVector(1000));

	// Find Monster Spawner
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATDGrid::StaticClass(), FoundActors);
    
	if (FoundActors.Num() > 0)
	{
		Grid = Cast<ATDGrid>(FoundActors[0]);
	}

	Gold = InitialGold;
	HealthAbility = FTDAbility(ETDAbilityType::Health, InitialHealth);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	OnGoldChanged.Broadcast(GetGold());
	OnHealthChanged.Broadcast(GetHealth());
	OnSelectedTowerChanged.Broadcast(false, 0);

	int MachineGunTowerPrice = MachineGunTowerClass.GetDefaultObject()->GetBuyPrice();
	int FrostTotemTowerPrice = FrostTotemTowerClass.GetDefaultObject()->GetBuyPrice();
	int GrenadeLauncherTowerPrice = GrenadeLauncherTowerClass.GetDefaultObject()->GetBuyPrice();
	int TeslaTowerPrice = TeslaTowerClass.GetDefaultObject()->GetBuyPrice();

	OnInitTowersPrice.Broadcast(MachineGunTowerPrice, FrostTotemTowerPrice, GrenadeLauncherTowerPrice, TeslaTowerPrice);
}

int ATDPlayerController::GetGold() const
{
	return Gold;
}

void ATDPlayerController::AddGold(int GoldToAdd)
{
	Gold += GoldToAdd;
	OnGoldChanged.Broadcast(Gold);
}

void ATDPlayerController::RemoveGold(int GoldToRemove)
{
	Gold -= GoldToRemove;
	OnGoldChanged.Broadcast(Gold);
}

int ATDPlayerController::GetHealth() const
{
	return  HealthAbility.GetCurrentValue();
}

void ATDPlayerController::RemoveHealth(int HealthToRemove)
{
	HealthAbility.ApplyEffect(HealthToRemove);

	if (HealthAbility.GetCurrentValue() <= 0)
		RestartLevel();
	
	OnHealthChanged.Broadcast(GetHealth());
}

void ATDPlayerController::OnClick()
{
	ATDCell* CellClicked = GetCellUnderMouse();

	if (CellClicked)
	{
		if (CellClicked->bIsOccuped || !CellClicked->bIsActive)
			return;

		int Price = 0;
	
		TSubclassOf<ATDTower> TowerClass = GetTowerClassFromType(CurrentTowerTypeSelected);
		if (!TowerClass)
			return;
	
		if (const ATDTower* DefaultTower = TowerClass.GetDefaultObject())
			Price = DefaultTower->GetBuyPrice();

		if (Price > GetGold())
			return;

		// SpawnActor
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		ATDTower* NewTower = GetWorld()->SpawnActor<ATDTower>(TowerClass, CellClicked->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
		NewTower->X = CellClicked->X;
		NewTower->Y = CellClicked->Y;
		
		CellClicked->bIsOccuped = true;
		RemoveGold(Price);
	}
	else
	{
		ATDTower* TowerClicked = GetTowerUnderMouse();

		if (!TowerClicked)
			return;
		
		CurrentSelectedTower = TowerClicked;
		int UpgradePrice = CurrentSelectedTower->GetUpgradePrice();
			
		OnSelectedTowerChanged.Broadcast(true, UpgradePrice);
	}
}

TSubclassOf<ATDTower> ATDPlayerController::GetTowerClassFromType(ETowerType TowerType) const
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

void ATDPlayerController::DestroyTower()
{
	ATDCell* CellUnderTower = Grid->GetGridCell(CurrentSelectedTower->X, CurrentSelectedTower->Y);

	if (CellUnderTower)
		CellUnderTower->bIsOccuped = false;

	CurrentSelectedTower->Destroy();
	CurrentSelectedTower = nullptr;
	OnSelectedTowerChanged.Broadcast(false, 0);
}

void ATDPlayerController::UpgradeTower()
{
	if (GetGold() < CurrentSelectedTower->GetUpgradePrice())
		return;
	
	RemoveGold(CurrentSelectedTower->GetUpgradePrice());
	
	CurrentSelectedTower->Upgrade();
	CurrentSelectedTower = nullptr;
	OnSelectedTowerChanged.Broadcast(false, 0);
}

ATDCell* ATDPlayerController::GetCellUnderMouse()
{
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		return Cast<ATDCell>(HitResult.GetActor());
	}
	return nullptr;
}

ATDTower* ATDPlayerController::GetTowerUnderMouse()
{
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		return Cast<ATDTower>(HitResult.GetActor());
	}
	return nullptr;
}


