// Copyright Mirza Besic 2016

#include "BattleTanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

/** path following: request new velocity */
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	/* Get the current forward direction as a normalized value. 
	We get a normalized value because we only need direction. This
	is the direction the tank is currently facing. */
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	/* Get the intended move direction we want the tank to go in next. 
	We're only interested in the direction in which the AI is asking us to move, 
	which is why we get a normal. We will decide how fast we will move in this direction. */
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	/* Set the forward movement to the dot product of the tanks current vector 
	and the intended vector. This gives us the angle between these two vectors.
	The tank goes forward at an appropriate speed depending on the difference between 
	where the AI wants it to be facing and where the Tank is facing.
	
	If the angle between ForwardIntention and TankForward vector is 0 degrees, 
	then the tank is already facing in the direction the AI wants it to go, so 
	go full speed at 1. As the angle goes down towards 90 degrees; meaning the AI intends 
	to go full right, the speed goes down to 0 following the cosine curve. 
	Similarly when the angle reaches 180 degrees, acording to the cosine curve
	the speed will be -1 meaning full backwards at that point. */
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	/*  The cross product of two vectors is always perpendicular to both of the vectors which
	were "crossed". One important example of the use of Cross Product is in torque or moment.

	The cross product here is the magnitude of the vectors TankForward and AIForwardIntention.
	And then, it's sin of the angle between the two, different to before by 90 degrees times n, 
	where n is a unit vector perpendicular to the plane defined by TankForward and AIForwardIntention. 

	It measures perpendicularity and is at maxiumu value when the vectors are perpendicular and zero 
	when they are parallel. Always orthogonal to both. The order of operation matters, if you swap 
	TankForward and AIForwardIntention the n direction will be flipped. 

	Following the sine curve, if there's no angle, i.e. if the AIForwardIntention is already alligned 
	with it's TankFroward, then don't turn right at all. As we move to 90 degrees, turn right as fast 
	as possible (1). At 180 degrees out don't turn right at all. As   approach and hit 270 degrees we
	turn right as fast as possible in the opposite direction (-1) therefore effectively turning left. */
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("ForwardThrow: %f RightThrow: %f"), ForwardThrow, RightThrow);
}

/* Initialization is done in blueprint where track assets are assigned to tracks being initialized. */
void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	/*Ensure that we have a left and right track assigned in BP and initialized. */
	if (!ensure(LeftTrack && RightTrack)) { return; }
	/* Throttle is clamped to -1, 1 so players can't overdrive. */
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	/*Ensure that we have a left and right track assigned in BP and initialized. */
	if (!ensure(LeftTrack && RightTrack)) { return; }
	/* Throttle is clamped to -1, 1 so players can't overdrive. */
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}