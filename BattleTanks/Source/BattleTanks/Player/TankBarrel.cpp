// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed) 
{
	///Move the barrel the right amount this frame
	/* Clamp relative speed to max/min values */
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	/* Calculate elevation change. MaxDegreesPerSecond is visible in UE4 so the turn speed can be changed there. 
	Also, multiplying by delta time makes it account for the users framerate.*/
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; 

	/* Calculate what the new elevation would be given the current elevation. */
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	/* Clamp the movement of the up/down movement of the barrel to MinElevationDegrees and MaxElevationDegrees,
	both are visible in UE4 and can be adjusted there. */
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	/* Set the new elevation. */
	SetRelativeRotation(FRotator(Elevation, 0, 0));

	/// DEBUG LOG
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel-Elevate() called at speed %f"), Time, RelativeSpeed);
}