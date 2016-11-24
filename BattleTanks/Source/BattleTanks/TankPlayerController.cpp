// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before anything else

	auto ControlledTank = GetControlledTank();
	//protecting the pointer
	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a tank!"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing: %s"), *ControlledTank->GetName());

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

