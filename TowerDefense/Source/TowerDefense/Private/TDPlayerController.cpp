// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ATDGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	Gold = InitialGold;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

ATDPlayerController::ATDPlayerController(): InitialGold(0), GameMode(nullptr), Gold(0)
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

int ATDPlayerController::GetGold() const
{
	return Gold;
}

void ATDPlayerController::AddGold(int GoldToAdd)
{
	Gold += GoldToAdd;
}

void ATDPlayerController::OnClick()
{
	ATDCell* CellClicked = GetCellUnderMouse();

	if (CellClicked == nullptr || CellClicked->bIsOccuped || !CellClicked->bIsActive)
		return;

	if (GameMode == nullptr)
		return;

	GameMode->InstantiateTower(GetTowerClassFromType(CurrentTowerType), CellClicked->GetActorLocation());
	CellClicked->bIsOccuped = true;
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


