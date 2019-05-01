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

	/* Match with the AI/SentryBlackboard */
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
	/* Ensure that the current stimulus is active before allowing
	the Tank Sentry to fire */
	ATankSentry* TankSentry = Cast<ATankSentry>(GetPawn());
	if (CurrentStimulus.IsActive())
	{
		/* Call the fire function on the controlled pawn.
		Currently it's the TankSentry*/
		TankSentry->TakeAimAndFireOnSensedTarget();
	}

	/* Check to see if the stimulus is expired by comparing the current age to the max age
	set in the constructor */
	if (CurrentStimulus.GetAge() > SightConfig->GetMaxAge())
	{
		/*Reset*/
		SetTargetEnemy(nullptr);
	}

}


void ASentryAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	/* Get the controlled pawn */
	ATankSentry* TankSentry = Cast<ATankSentry>(InPawn);

	/* Protect pawn pointer */
	if (TankSentry)
	{
		/* Ensure that the behavior tree asset exists*/
		if (TankSentry->BehaviorTree->BlackboardAsset)
		{
			/* Initialize the blackboard component that is on the controlled pawn, basically 
			telling the pawn to run it's behaviorTree with the assigned blackboard asset. */
			BlackboardComp->InitializeBlackboard(*TankSentry->BehaviorTree->BlackboardAsset);

			/* Make sure the Blackboard has the type of bot we possessed */
			SetBlackboardBotType(TankSentry->BotType);
		}

		/* Now that the blackboard component has been initialized to the TankSentry's blackboard asset, 
		the behavior component begins TankSentry's behavior tree and associated logic. */
		BehaviorComp->StartTree(*TankSentry->BehaviorTree);
	}

	// Bind the death method
	TankSentry->OnDeath.AddUniqueDynamic(this, &ASentryAIController::OnPossessedTankDeath);

	/* Setup the AI Controller to bind the stimulus source to the controlled pawn, 
	this way we know from which pawns to listen to for perception updates.*/
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, HearingConfig->GetSenseImplementation(), GetPawn());
}

/* Source is the actor that was sensed, the Stimulus is the type of sense such as hearing or sight. 
Currently, both hearing and sight do the same thing; however...*/
// TODO Override or create seperate functions for hearing and sight when I need different behavior based on either sense... .
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

	/* Currently both sight and hearing trigger the same behavior in the sentry.*/
	/* TODO Create two seperate methods that do different things for both sight and hearing senses, 
	I'm not sure what but it makes sense that they wouldn't do the same thing - it works for now though.*/
	if (Stimulus.Type == SightConfig->GetSenseID() || Stimulus.Type == HearingConfig->GetSenseID())
	{
		/* Set the sensed pawn as the target enemy. */
		ATrackedVehicle* SensedPawn = Cast<ATrackedVehicle>(Source);
		if(SensedPawn){ SetTargetEnemy(SensedPawn); }	
	}
}

/* Detaches AI controller when tank gets destroyed. */
void ASentryAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Inside OnPossessedTankDeath"));
	/* Mark any sensed targets no longer sensed */
	CurrentStimulus.MarkNoLongerSensed();

	if (!(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
	// GetPawn()->Destroy();
	this->UnPossess();
	this->Destroy();
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


ATrackedVehicle* ASentryAIController::GetTargetEnemy()
{
	if (BlackboardComp)
	{
		return Cast<ATrackedVehicle>(BlackboardComp->GetValueAsObject(TargetEnemyKeyName));
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
