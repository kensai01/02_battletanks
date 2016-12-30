// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed) 
{
	///Move the barrel the right amount this frame
	// clamp relative speed to max/min values
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	// calculate elevation change
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; //delta time makes it account for frame rate

	// calculate what the new elevation would be given the current elevation
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// clamp the movement of the 
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	// set the new rotation
	SetRelativeRotation(FRotator(Elevation, 0, 0));

	//Given a max elevation speed and frame time
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel-Elevate() called at speed %f"), Time, RelativeSpeed);
}