// Copyright Mirza Besic 2016

#include "BattleTanks.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can implement OnDeath
#include "TrackedVehicle.h"
#include "../Types.h"

//void ATankAIController::SetPerceptionStatus(EPerceptionStatus NextPerceptionStatus)
//{
//	PerceptionStatus = NextPerceptionStatus;
//}
//
//EPerceptionStatus ATankAIController::GetPerceptionStatus() const
//{
//	return PerceptionStatus;
//}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATrackedVehicle>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

//// Called every frame
//void ATankAIController::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
//	auto ControlledTank = GetPawn();
//
//	if (!ensure(PlayerTank && ControlledTank)) { return; }
//	
//	if (PerceptionStatus == EPerceptionStatus::Seeking) {
//		
//		UE_LOG(LogTemp, Warning, TEXT("Found Enemy, SEARCH AND DESTROY!"))
//
//		// Move towards the player
//		MoveToActor(PlayerTank, AcceptanceRadius);  // TODO Check radius is in cm
//
//		// Aim towards the player
//		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
//		AimingComponent->AimAt(PlayerTank->GetActorLocation());
//
//		// If aim & locked Fire towrads the player
//		if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
//		{
//			AimingComponent->Fire(); // TODO limit firing rate
//		}
//	}
//
//}





