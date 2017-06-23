// Copyright MB

#pragma once

#include "BattleTanks.h"
#include "MMTPawn.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Types.h"
#include "TrackedVehicle.generated.h"


/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTrackedVehicleDelegate);

UCLASS()
class BATTLETANKS_API ATrackedVehicle : public AMMTPawn
{
	GENERATED_BODY()

public:
	/// CONSTRUCTOR AND OVERRIDDEN FUNCTIONS
	virtual void BeginPlay() override;
	// Called by engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	// Sets default values for this character's properties
	//ATrackedVehicle(const class FObjectInitializer& ObjectInitializer);



	/// SOUND AND NOISE HANDLING
	/* MakeNoise hook to trigger AI noise emitting (Loudness between 0.0-1.0)  */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void MakePawnNoise(float Loudness);
	UFUNCTION(BlueprintCallable, Category = "AI")
	float GetLastNoiseLoudness();
	UFUNCTION(BlueprintCallable, Category = "AI")
	float GetLastMakeNoiseTime();

	float LastMakeNoiseTime;
	float LastNoiseLoudness;

	/* MakeSoundTankFiring is blueprint callable in order to be able to attach
	the sound mechanism to the firing input mechanism which was set up in blueprint
	along with the rest of input controlls.*/
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void  MakeSoundTankFiring();
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SoundTakeHit;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SoundTankFiring;

	/// TARGETING SYSTEM
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void LockAimTowardsTarget(FVector HitLocation, bool targEnemy);
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void UnlockAimTowardsTarget();
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void SeekAndSetNearestEnemy_new(ATrackedVehicle* EnemyTank);
	UFUNCTION(BlueprintCallable, Category = "Targeting")
	float DistanceFromEnemy(ATankSentry* enemy);
	
	UFUNCTION(Category = "Targeting")
	bool Trace(UWorld* World,
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		bool ReturnPhysMat);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float ClosestTargetDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	ATankSentry* NearestTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	bool targetingEnemy = false;


	/// HEALTH AND DAMAGE HANDLING
	// Returns current health as a pct of starting health, between 0 and 1
	UFUNCTION(BluePrintPure, Category = "Health")
	float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsAlive() const;

	FTrackedVehicleDelegate OnDeath;

private:
	/// MUST STAY PRIVATE
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	/* Tracks noise data used by the pawn sensing component */
	UPawnNoiseEmitterComponent* NoiseEmitterComp;
	
};
