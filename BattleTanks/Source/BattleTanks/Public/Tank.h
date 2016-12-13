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
	/* Tracks noise data used by the pawn sensing component */
	UPawnNoiseEmitterComponent* NoiseEmitterComp;

public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	float GetLastNoiseLoudness();

	UFUNCTION(BlueprintCallable, Category = "AI")
	float GetLastMakeNoiseTime();

	/* MakeNoise hook to trigger AI noise emitting (Loudness between 0.0-1.0)  */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void MakePawnNoise(float Loudness);

	// Returns current health as a pct of starting health, between 0 and 1
	UFUNCTION(BluePrintPure, Category = "Health")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerCondition")
	bool IsAlive() const;

	virtual void BeginPlay() override;

	// Called by engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Sets default values for this character's properties
	ATank(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SoundTakeHit;

	FTankDelegate OnDeath;

	float LastMakeNoiseTime;
	float LastNoiseLoudness;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "PlayerCondition", Replicated)
	float Health;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;
};
