// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

//forward declaration
class UTankTrack;
/**
 * Responsible for driving the tank tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);


private:
	// TODO check best protection of this method
	/** path following: request new velocity 
	 Called from the pathfinding logic by the AI controller */
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
