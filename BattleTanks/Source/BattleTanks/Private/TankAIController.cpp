// Copyright Mirza Besic 2016

#include "BattleTanks.h"
#include "../Public/Tank.h"
#include "../Public/TankAIController.h"

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank))
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);  // TODO Check radius is in cm

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire towrads the player
		ControlledTank->Fire(); // TODO limit firing rate
	}
}

///Code below was in-lined into the Tick method
/*
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
*/

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
