// Copyright MB

#include "BattleTanks.h"
#include "BTTask_FindPatrolLocation.h"
#include "AI/BotWaypoint.h"
#include "NPC/SentryAIController.h"


/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASentryAIController* MyController = Cast<ASentryAIController>(OwnerComp.GetAIOwner());
	if (MyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ABotWaypoint* MyWaypoint = MyController->GetWaypoint();
	if (MyWaypoint)
	{
		/* Find a position that is close to the waypoint. We add a small random to this position to give build predictable patrol patterns  */
		const float SearchRadius = 200.0f;
		const FVector SearchOrigin = MyWaypoint->GetActorLocation();
		const FVector Loc = UNavigationSystem::GetRandomPointInNavigableRadius(MyController, SearchOrigin, SearchRadius);
		if (Loc != FVector::ZeroVector)
		{
			/* The selected key should be "PatrolLocation" in the BehaviorTree setup */
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), Loc);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}




