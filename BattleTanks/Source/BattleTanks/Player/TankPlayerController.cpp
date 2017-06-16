// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TrackedVehicle.h"

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		/* Posess a tank character. */
		auto PossessedTank = Cast<ATrackedVehicle>(InPawn);

		/* Ensure that we have a posessed character to play with. */
		if (!ensure(PossessedTank)) { return; }

		/* Subscribe our local method to the tank's death event */
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	/* Detach from the controller, effectively rendering the player dead. */
	StartSpectatingOnly();
	DisplayGameOverScreen();
}

void ATankPlayerController::BeginPlay()
{
	/* Call the default behavior before anything else. */
	Super::BeginPlay();

	/* Ensure that we are possessing a tank character. */
	if (!GetPawn()) { return; } 

	/* Get the aiming component in order to be able to fire on the target. */
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	/* Ensure that we have an aiming component to fire with. */
	if (!ensure(AimingComponent)) { return; }

	/* Blueprint callable event that is called in the PlayerController blueprint
	in order to create the player user interface widget (crosshair, ammo count etc.). */
	FoundAimingComponent(AimingComponent);

	/// DEBUG LOG
	//auto ControlledTank = GetPawn();
	//if (!ensure(ControlledTank)) 	//protecting the pointer
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a tank!"));
	//}
	//else UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing: %s"), *ControlledTank->GetName());
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	/* Ensure that we are posessing a pawn. */
	if (!(GetPawn())) { return; } 

	/* Get the aiming component. */
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	/* Ensure that we have an aiming component. */
	if (!ensure(AimingComponent)) { return; }

	/* Out paramater. */
	FVector HitLocation; 

	/* Get world location of linetrace through crosshair, true if hits landscape. */
	bool bGothitLocation = GetSightRayHitLocation(HitLocation);

	if (bGothitLocation)
	{
		/* Tells controlled tank to aim at this point. */
		AimingComponent->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const 
{
	/// FIND THE CROSSHAIR POSITION
	/* initialize viewport size. */
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	/* Location on screen that's half way across and 2/3rds of the way up the screen. */
	auto ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);


	/// DE-PROJECT THE SCREEN POSITION OF THE CROSSHAIR TO A WORLD DIRECTION
	/* Out paramater. */
	FVector LookDirection;

	/* De-project the screen position of the crosshair to a world direction.
	Convert current mouse 2D position to World Space 3D position and direction.
	Returns false if unable to determine value.*/
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		/* Line-trace along that direction (look direction) */
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}


	// See what we hit after (up to max range)
	return false;
}

/* De-project the screen position of the crosshair to a world direction. */
bool ATankPlayerController::GetLookDirection(FVector2D &ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation; // unused paramater

	/* Convert current mouse 2D position to World Space 3D position and direction.
	Returns false if unable to determine value.*/
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	/* Stores the resulting hit information. */
	FHitResult HitResult;

	/* Start location is the camera location of the player character. */
	auto StartLocation = PlayerCameraManager->GetCameraLocation();

	/* End Location vector, the point we are looking/pointing at. */
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	/* Trace a ray against the world using a specific channel and return the first blocking hit
	TRUE if a blocking hit is found. */
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation, 
		ECollisionChannel::ECC_Camera)
		)
	{
		/* Lince trace worked, we assign the resulting location to the out paramater HitLocation. */
		HitLocation = HitResult.Location;
		return true;
	}
	/* If line trace didn't work, return zero vector. */
	HitLocation = FVector(0);
	return false; 
}

