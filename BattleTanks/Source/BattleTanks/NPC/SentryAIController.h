// Copyright MB

#pragma once

#include "AIController.h"
#include "Player/Tank.h"
#include "TankSentry.h"
#include "AI/BotWaypoint.h"
#include "SentryAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ASentryAIController : public AAIController
{
	GENERATED_BODY()
		ASentryAIController(const class FObjectInitializer& ObjectInitializer);

		/* Called whenever the controller possesses a character bot. */
		virtual void Possess(class APawn* InPawn) override;

		/* Called whenever the controlled pawn is killed in order to stop the behavior tree from running. */
		virtual void UnPossess() override;

		/* Handles the firing mechanism for the possesed and enemy target sense reset. */
		virtual void Tick(float DeltaTime) override;

		/* Behavior and Blackboard components defined here are assigned to
		blackboard and behavior components of the pawn that is possessed. */
		UBehaviorTreeComponent* BehaviorComp;
		UBlackboardComponent* BlackboardComp;

		/* Used for configuration of sight and hearing in the constructor. */
		class UAISenseConfig_Sight* SightConfig;
		class UAISenseConfig_Hearing* HearingConfig;

		/* Used to capture the stimulus as a class variable and perform operations on it */
		FAIStimulus CurrentStimulus;

		/// BLACKBOARD KEYS
		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetEnemyKeyName;
		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PatrolLocationKeyName;
		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName CurrentWaypointKeyName;
		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BotTypeKeyName;

		/* Handles the death of the possesed character, ejecting the AI controller */
		UFUNCTION()
		void OnPossessedTankDeath();

		/* Handles the perception updates and sets the stimulus class variable (CurrentStimulus)
		as well as sets the target enemy as the sensed pawn. */
		UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Source, FAIStimulus Stimulus);

	public:
		/* Returns a bot waypoint which is derived from a target point*/
		ABotWaypoint* GetWaypoint();

		/* Get the target enemy of ATank type*/
		/* TODO seperate the implementation from specifying 
		ATank but have it be passed in as a type so that 
		it can be used for many different type of
		enemies besides just a tank. */
		ATank* GetTargetEnemy();

		void SetWaypoint(ABotWaypoint* NewWaypoint);

		void SetTargetEnemy(APawn* NewTarget);

		void SetBlackboardBotType(EBotBehaviorType NewType);

		/** Returns BehaviorComp subobject **/
		FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp()const { return BehaviorComp; }

		FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	
};
