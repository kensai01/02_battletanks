// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankAIController.h"

// returns ai controlled tank
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
// returns player controlled tank 
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before anything else

	auto PlayerTank = GetPlayerTank();
	//protecting the pointer
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is not able to find player."));
	}
	else UE_LOG(LogTemp, Warning, TEXT("AIController is targeting: %s"), *PlayerTank->GetName());

	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}
