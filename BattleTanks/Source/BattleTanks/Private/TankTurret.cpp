// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "../Public/TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	///Move the barrel the right amount this frame
	// clamp relative speed to max/min values
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	// calculate elevation change
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; //delta time makes it account for frame rate

																							   // calculate what the new elevation would be given the current elevation
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	// set the new rotation
	SetRelativeRotation(FRotator(0, Rotation, 0));

	//Given a max elevation speed and frame time
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel-Elevate() called at speed %f"), Time, RelativeSpeed);
}

