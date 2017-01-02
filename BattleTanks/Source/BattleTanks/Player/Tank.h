// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Types.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	/// CONSTRUCTOR AND OVERRIDDEN FUNCTIONS
	virtual void BeginPlay() override;
	// Called by engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	// Sets default values for this character's properties
	ATank(const class FObjectInitializer& ObjectInitializer);


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



	/// HEALTH AND DAMAGE HANDLING
	// Returns current health as a pct of starting health, between 0 and 1
	UFUNCTION(BluePrintPure, Category = "Health")
	float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsAlive() const;

	FTankDelegate OnDeath;

private:
	/// MUST STAY PRIVATE
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	/* Tracks noise data used by the pawn sensing component */
	UPawnNoiseEmitterComponent* NoiseEmitterComp;
};
