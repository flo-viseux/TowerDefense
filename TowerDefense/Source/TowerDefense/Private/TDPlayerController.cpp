// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerController.h"

int ATDPlayerController::GetGold() const
{
	return Gold;
}

void ATDPlayerController::AddGold(int GoldToAdd)
{
	Gold += GoldToAdd;
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
