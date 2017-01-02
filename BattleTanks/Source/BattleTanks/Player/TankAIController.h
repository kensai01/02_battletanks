// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Types.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "State")
	//EPerceptionStatus GetPerceptionStatus() const;

	//UFUNCTION(BlueprintCallable, Category = "State")
	//void SetPerceptionStatus(EPerceptionStatus NextPerceptionStatus);

protected:
	// How close the AI can get
	UPROPERTY(EditDefaultsOnly, Category = "Setup") 
	float AcceptanceRadius = 8000;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	// Called every frame
	//virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnPossessedTankDeath();

	//set the default value to patrolling
	UPROPERTY(VisibleAnywhere, Category = "State")
	EPerceptionStatus PerceptionStatus = EPerceptionStatus::Patrolling;
};
