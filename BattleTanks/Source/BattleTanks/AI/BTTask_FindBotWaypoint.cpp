// Copyright MB

#include "BattleTanks.h"
#include "BTTask_FindBotWaypoint.h"
#include "AI/BotWaypoint.h"
#include "NPC/SentryAIController.h"


/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTask_FindBotWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/* Get and protect the AI Controller. */
	ASentryAIController* MyController = Cast<ASentryAIController>(OwnerComp.GetAIOwner());

	/* If there is no Sentry AI Controller, node fails. */
	if (MyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	/* Get the current waypoint from the AI Controller. */
	ABotWaypoint* CurrentWaypoint = MyController->GetWaypoint();

	/* Local variable to store the new waypoint. */ 
	AActor* NewWaypoint = nullptr;

	/* Iterate all the bot waypoints in the current level and find a new random waypoint to set as destination. */
	TArray<AActor*> AllWaypoints;

	/* Find all Actors in the world of the specified class (ABotWaypoint). This is a slow operation, use with caution e.g. do not use every frame. */
	UGameplayStatics::GetAllActorsOfClass(MyController, ABotWaypoint::StaticClass(), AllWaypoints);

	/* If no bot waypoints are found in the world, node fails. */
	if (AllWaypoints.Num() == 0)
		return EBTNodeResult::Failed;

	/* Find a new waypoint randomly by index (this can include the current waypoint) */
	/* For more complex or human AI you could add some weights based on distance and other environmental conditions here */
	/* TODO for more complex AI multiple methods could be created here that utilize the found waypoints to 
	create functionality such as random waypoints used below, select the closest one, a specific one or a method that utilizes 
	a combination of conditions to create specified behavior. */
	NewWaypoint = AllWaypoints[FMath::RandRange(0, AllWaypoints.Num() - 1)];

	/* Assign the new waypoint to the Blackboard */
	if (NewWaypoint)
	{
		/* The selected key should be "CurrentWaypoint" in the BehaviorTree setup */
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), NewWaypoint);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}





