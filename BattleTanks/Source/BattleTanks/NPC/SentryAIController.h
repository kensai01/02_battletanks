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

		/* Called whenever the controller possesses a character bot */
		virtual void Possess(class APawn* InPawn) override;

		virtual void UnPossess() override;

		virtual void Tick(float DeltaTime) override;

		UBehaviorTreeComponent* BehaviorComp;

		UBlackboardComponent* BlackboardComp;

		///EXPERIMENTAL NEW AIPERCEPTION SYSTEM
		//UPROPERTY(VisibleAnywhere, Category = "AI")
		//UAIPerceptionComponent* PerceptionComponent;

		class UAISenseConfig_Sight* SightConfig;
		class UAISenseConfig_Hearing* HearingConfig;

		FAIStimulus CurrentStimulus;

		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetEnemyKeyName;

		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PatrolLocationKeyName;

		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName CurrentWaypointKeyName;

		UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BotTypeKeyName;

		UFUNCTION()
		void OnPossessedTankDeath();

		UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Source, FAIStimulus Stimulus);

	public:

		ABotWaypoint* GetWaypoint();

		ATank* GetTargetEnemy();

		void SetWaypoint(ABotWaypoint* NewWaypoint);

		void SetTargetEnemy(APawn* NewTarget);

		void SetBlackboardBotType(EBotBehaviorType NewType);

		/** Returns BehaviorComp subobject **/
		FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp()const { return BehaviorComp; }

		FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	
};
