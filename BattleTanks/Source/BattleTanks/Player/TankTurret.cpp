// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	/// MOVE THE BARREL THE RIGHT AMOUNT THIS FRAME
	/* Clamp relative speed to max/min values*/
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	/* Calculate rotation change, delta time makes it account for frame rate. */
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	/* Calculate what the new rotation would be given the current rotation. */
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	/* Set the new rotation. */
	SetRelativeRotation(FRotator(0, Rotation, 0));

	//Given a max elevation speed and frame time

	/// LOG
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel-Elevate() called at speed %f"), Time, RelativeSpeed);
}

