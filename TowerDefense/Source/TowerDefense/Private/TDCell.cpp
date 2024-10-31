// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCell.h"
#include "Components/BoxComponent.h"

// Sets default values
ATDCell::ATDCell()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create a box component to represent the cell
	UBoxComponent* BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 5.0f));
	RootComponent = BoxComp;

}

void ATDCell::BeginPlay()
{
	Super::BeginPlay();

	if (!bIsActive)
		this->SetActorHiddenInGame(true);
	else
		this->SetActorHiddenInGame(false);
}

void ATDCell::OnCellClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnCellClicked"));

	OnClickedEvent.Broadcast(this->GetActorLocation());
}

