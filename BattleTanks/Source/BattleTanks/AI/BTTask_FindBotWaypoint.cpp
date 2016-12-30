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
	ASentryAIController* MyController = Cast<ASentryAIController>(OwnerComp.GetAIOwner());
	if (MyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ABotWaypoint* CurrentWaypoint = MyController->GetWaypoint();
	AActor* NewWaypoint = nullptr;

	/* Iterate all the bot waypoints in the current level and find a new random waypoint to set as destination */
	TArray<AActor*> AllWaypoints;
	UGameplayStatics::GetAllActorsOfClass(MyController, ABotWaypoint::StaticClass(), AllWaypoints);

	if (AllWaypoints.Num() == 0)
		return EBTNodeResult::Failed;

	/* Find a new waypoint randomly by index (this can include the current waypoint) */
	/* For more complex or human AI you could add some weights based on distance and other environmental conditions here */
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





