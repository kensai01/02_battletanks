// Copyright MB

#include "BattleTanks.h"
#include "SentryAIController.h"
#include "TankSentry.h"
#include "Player/Tank.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

/* Perception Include */
#include "Perception/PawnSensingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"



ASentryAIController::ASentryAIController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	/// BLACKBOARD AND BEHAVIOR TREE SETUP
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	/* Match with the AI/ZombieBlackboard */
	PatrolLocationKeyName = "PatrolLocation";
	CurrentWaypointKeyName = "CurrentWaypoint";
	BotTypeKeyName = "BotType";
	TargetEnemyKeyName = "TargetEnemy";

	/// AI PERCEPTION SETUP
	/* Setup of the perception component */
	SetPerceptionComponent(*ObjectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("AI Perception Component")));
	//PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));

	/* Setup of the sight configuration */
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	/* Setup of the hearing configuration */
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	/* Set sight as the dominant sense*/
	GetAIPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());

	/* Sight Configuration */
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = (1200.0f);
	SightConfig->PeripheralVisionAngleDegrees = 140.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->SetMaxAge(5.0f);

	/* Hearing Configuration */
	HearingConfig->HearingRange = 1400.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->SetMaxAge(5.0f);

	/* Configure the perception component with setup sight and hearing components */
	GetAIPerceptionComponent()->ConfigureSense(*SightConfig);
	GetAIPerceptionComponent()->ConfigureSense(*HearingConfig);

	/* Bind the OnTargetPerceptionUpdated delegate to our class,
	this allows us to create and call this method when an actor is sensed in orer to do stuff such as eun behavior trees.*/
	GetAIPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ASentryAIController::OnTargetPerceptionUpdated);

	/* Initializes PlayerState so we can assign a team index to AI */
	bWantsPlayerState = true;
}

void ASentryAIController::Tick(float DeltaTime)
{

	//ASentryAIController* AIController = Cast<ASentryAIController>(GetController());
	/* Ensure that the AIController is present to avoid having dead
	sentry tanks firing on the player when they get in sense radius */
	ATankSentry* TankSentry = Cast<ATankSentry>(GetPawn());
	if (CurrentStimulus.IsActive())
	{
		TankSentry->TakeAimAndFireOnSensedTarget();
	}

	/* Check if the last time we sensed a player is beyond the
	time out value to prevent bot from endlessly following a player.*/
	//CurrentTime = GetWorld()->TimeSeconds;
	//if (bSensedTarget && (CurrentTime - LastSeenTime) > SenseTimeOut)
		//&& (CurrentTime - LastHeardTime) > SenseTimeOut)
	//{

		//if (AIController)
		//{
			/* Reset */
			//bSensedTarget = false;
			//AIController->SetTargetEnemy(nullptr);

			/* Stop playing the search and destroy sound */
			// TODO Implement search and destroy sound/music
			//BroadcastUpdateAudioLoop(false);
		//}
	//}

	//auto CurrentTime = GetWorld()->TimeSeconds;
	//auto LastSeenTime = CurrentTime - CurrentStimulus.GetAge();
	if (CurrentStimulus.GetAge() > SightConfig->GetMaxAge())
	{
		SetTargetEnemy(nullptr);
	}

}


void ASentryAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	ATankSentry* TankSentry = Cast<ATankSentry>(InPawn);
	if (TankSentry)
	{
		if (TankSentry->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*TankSentry->BehaviorTree->BlackboardAsset);

			/* Make sure the Blackboard has the type of bot we possessed */
			SetBlackboardBotType(TankSentry->BotType);
		}

		BehaviorComp->StartTree(*TankSentry->BehaviorTree);
	}

	// Bind the death method
	TankSentry->OnDeath.AddUniqueDynamic(this, &ASentryAIController::OnPossessedTankDeath);

	// Set up the AI Controller to bind the stimulus source to the controlled pawn
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetControlledPawn());
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, HearingConfig->GetSenseImplementation(), GetControlledPawn());
}

//	FAIStimulus& SetExpirationAge(float InExpirationAge) { ExpirationAge = InExpirationAge; return *this; }
//	FAIStimulus& SetStimulusAge(float StimulusAge) { Age = StimulusAge; return *this; }
//	FAIStimulus& SetWantsNotifyOnlyOnValueChange(bool InEnable) { bWantsToNotifyOnlyOnValueChange = InEnable; return *this; }
//	
//	FORCEINLINE float GetAge() const { return Strength > 0 ? Age : NeverHappenedAge; }
//	/** @return false when this stimulus is no longer valid, when it is Expired */
//FORCEINLINE bool AgeStimulus(float ConstPerceptionAgingRate)
//{
//	Age += ConstPerceptionAgingRate;
//	return Age < ExpirationAge;
// }
// FORCEINLINE bool WasSuccessfullySensed() const { return bSuccessfullySensed; }
// FORCEINLINE bool IsExpired() const { return bExpired; }
// FORCEINLINE void MarkNoLongerSensed() { bSuccessfullySensed = false; }
// FORCEINLINE void MarkExpired() { bExpired = true; MarkNoLongerSensed(); }
// FORCEINLINE bool IsActive() const { return WasSuccessfullySensed() == true && GetAge() < NeverHappenedAge; }
// FORCEINLINE bool WantsToNotifyOnlyOnPerceptionChange() const { return bWantsToNotifyOnlyOnValueChange; }
// FORCEINLINE bool IsValid() const { return Type != FAISenseID::InvalidID(); }



/* Source is the actor that was sensed, the Stimulus is the type of sense such as hearing or sight. 
Currently, both hearing and sight do the same thing; however...*/
// TODO Override or create seperate functions for hearing and sight when I need different behavior based on either sense
void ASentryAIController::OnTargetPerceptionUpdated(AActor * Source, FAIStimulus Stimulus)
{
	/* Update the stimulus variable in class with sensed stimulus in order to 
	be able to check the various statues and ages at various points OTHER than when
	OnTargetPerceptionUpdated gets triggered, this way we can do stuff with the stimulus in 
	the tick function for example. */
	CurrentStimulus = Stimulus;

	//ATankSentry* TankSentry = Cast<ATankSentry>(GetPawn());

	// Set the expiration age of the stimulus to 5 seconds
	// Should be automaticaly set as max of 5 seconds, need to test this
	// TODO Figure out setting MaxAge in constructor not here
	Stimulus.SetExpirationAge(5.0f);

	if (Stimulus.Type == SightConfig->GetSenseID() || Stimulus.Type == HearingConfig->GetSenseID())
		//&& (CurrentTime - LastHeardTime) > SenseTimeOut)
	{
		ATank* SensedPawn = Cast<ATank>(Source);
		if(SensedPawn){ SetTargetEnemy(SensedPawn); }	
	}
}




// TODO fix bug where tank keeps firing after being destroyed
void ASentryAIController::OnPossessedTankDeath()
{
	if (!(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}



void ASentryAIController::UnPossess()
{
	Super::UnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}

void ASentryAIController::SetWaypoint(ABotWaypoint* NewWaypoint)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(CurrentWaypointKeyName, NewWaypoint);
	}
}


void ASentryAIController::SetTargetEnemy(APawn* NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, NewTarget);
	}
}


ABotWaypoint* ASentryAIController::GetWaypoint()
{
	if (BlackboardComp)
	{
		return Cast<ABotWaypoint>(BlackboardComp->GetValueAsObject(CurrentWaypointKeyName));
	}

	return nullptr;
}


ATank* ASentryAIController::GetTargetEnemy()
{
	if (BlackboardComp)
	{
		return Cast<ATank>(BlackboardComp->GetValueAsObject(TargetEnemyKeyName));
	}

	return nullptr;
}


void ASentryAIController::SetBlackboardBotType(EBotBehaviorType NewType)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(BotTypeKeyName, (uint8)NewType);
	}
}
