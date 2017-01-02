// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Weapons/Projectile.h"
#include "Types.h"


/* Initialize the turret and barrel, this function is callable in blueprint where the 
barrel and turret will be set. */
void UTankAimingComponent::InitializeAim(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

/* Set default values for this component's properties */
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	/* So that first fire is after initial reload */
	LastFireTime = FPlatformTime::Seconds();
}

/* Handles the Firing Statuses */
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	/* Sets out of ammo status. */
	if (IsOutOfAmmo()) { FiringStatus = EFiringStatus::OutOfAmmo; }
	/* Sets reloading status. */
	else if (IsReloading()) { FiringStatus = EFiringStatus::Reloading;}
	/* Sets the aiming status. */
	else if (IsBarrelMoving()) { FiringStatus = EFiringStatus::Aiming; }
	/* Sets the target locked status. */
	// TODO Implement a feature here that prevents firing unless the enemy target is within the crosshair (reasonable threshold)
	else { FiringStatus = EFiringStatus::Locked; }
}

/* Returns true if tank runs out of ammo. */
bool UTankAimingComponent::IsOutOfAmmo()
{
	return RoundsLeft <= 0;
}

/* Sets true if the reload time has not yet elapsed. */
bool UTankAimingComponent::IsReloading()
{
	return (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	/* Get the direction the barrel's static mesh is pointing in. */
	auto BarrelForwardVector = Barrel->GetForwardVector();

	/* Compare the aim direction of our crosshair to the direction the barrel is pointing in 
	and if it's equal within an error margin of 1 pct return true. */
	return BarrelForwardVector.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Fire()
{
	/* Can fire only if not reloading or out of ammo. */
	if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming)
	{
		
		/* Ensure that we have both a barrel to fire from and a projectile to fire.*/
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		/* Spawn a projectile at the socket location on the barrel */
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		/* Launch the spawned projectile. */
		Projectile->LaunchProjectile(LaunchSpeed);

		/* Set the last time projectile was fired. */
		LastFireTime = FPlatformTime::Seconds();

		/* Decrement ammo. */
		RoundsLeft--;
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

/* Called by the Tank Player Controller */
void UTankAimingComponent::AimAt(FVector HitLocation) 
{
	/* Ensure that we have a barrel to aim with. */
	if (!ensure(Barrel)) { return; }
	
	/* Stores the launch velocity to be used. */
	FVector OutLaunchVelocity;

	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	/* Calculate the projectile velocity in order to hit the location calculated
	in player controller. */
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		1000, //sets radius of possible hit area, this way it's not 100% precise
		0, //gravity override
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	/*Checks if we have aim solution*/
	if (bHaveAimSolution)
	{
		/* Get a safe normal to get the direction normalized to a 0-1 value.*/
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		/* Moves the barrel towards the normalized aim direction. */
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	/* Ensure that we have a barrel and turret to turn and rotate. */
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	/* Work out difference between current barrel rotation and aim direction */
	/* Get the barrel rotation.*/
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();

	/* Get the aim direction rotation. */
	auto AimAsRotator = AimDirection.Rotation();

	/* To get the resulting correct rotation, 
	subtract the barrel rotation from the aim rotation*/
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	/* Finally, elevate the barrel based on the difference between the two rotations. */
	Barrel->Elevate(DeltaRotator.Pitch); 

	/* Always yaw(rotate turret) the shortest way, this is to prevent the barrel from going the 
	long way around the circle in certain instances when a shorter path could have 
	been chosen for a much quicker rotation. */
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		/* Rotation is less than 180 degrees so rotate normally.*/
		Turret->Rotate(DeltaRotator.Yaw);
	}
	/* Rotation is greater than 180 degrees,
	use a negative rotation in order to smoothly
	continue the aiming path without having the 
	barrel stop and go the other way around once you 
	go past the 180 degree spot relative to the 
	tanks position. */
	else Turret->Rotate(-DeltaRotator.Yaw);
}
