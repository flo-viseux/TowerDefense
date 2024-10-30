// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCell.h"

// Sets default values
ATDCell::ATDCell()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

