// Copyright Mirza Besic 2016

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

// forward declaration
class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	

private:

	/* Start the tank moving the barrel so that a 
	shot would hit where the crosshair intersects the world*/
	void AimTowardsCrosshair();

	/* Look through the chrosshair via linetrace and determine hit location*/
	/* Return an OUT paramater, true if hit langugage*/
	bool GetSightRayHitLocation(FVector & HitLocation) const;

	// Returns the de-projected screen position of the crosshair to a world direction 
	bool GetLookDirection(FVector2D &ScreenLocation, FVector &LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;
};
