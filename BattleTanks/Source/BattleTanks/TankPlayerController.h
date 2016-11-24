// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATank* GetControlledTank() const; 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
private:

	/*Start the tank moving the barrel so that a 
	shot would hit where the crosshair intersects the world*/
	void AimTowardsCrosshair();

	/*Look through the chrosshair via linetrace and determine hit location*/
	/*Return an OUT paramater, true if hit langugage*/
	bool GetSightRayHitLocation(FVector & HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
};
