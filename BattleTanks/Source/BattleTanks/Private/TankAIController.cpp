// Copyright Mirza Besic 2016

#include "BattleTanks.h"
#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);  // TODO Check radius is in cm
	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire towrads the player
	AimingComponent->Fire(); // limit firing rate
	
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
