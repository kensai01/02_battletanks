// Copyright MB

#include "BattleTanks.h"
#include "Public/SentryAIController.h"
#include "Public/TankSentry.h"
#include "Public/Tank.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"



ASentryAIController::ASentryAIController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	/* Match with the AI/ZombieBlackboard */
	PatrolLocationKeyName = "PatrolLocation";
	CurrentWaypointKeyName = "CurrentWaypoint";
	BotTypeKeyName = "BotType";
	TargetEnemyKeyName = "TargetEnemy";

	/* Initializes PlayerState so we can assign a team index to AI */
	bWantsPlayerState = true;
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
	TankSentry->OnDeath.AddUniqueDynamic(this, &ASentryAIController::OnPossessedTankDeath);
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
