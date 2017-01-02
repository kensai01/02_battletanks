// Copyright MB

#include "../BattleTanks.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"
#include "AIController.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	/* Get the AI Controller */
	auto AIController = OwnerComp.GetAIOwner();

	/* Get the controlled pawn*/
	auto ControlledPawn = AIController->GetPawn();

	/* Then get all the patrol points*/
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	/* Protect against no patrol route component */
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	/* Get the patrol points as a TArray of patrol point AActor */
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	/* Warn against empty patrol routes */
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sentry is missing patrol points!"))
		return EBTNodeResult::Failed;
	}

	/* Get the blackboard component */
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	/* Get the current index that indicates which patrol point we are currently looking at in the patrol points array*/
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	/* Set the next waypoint in the patrol route to the patrol point elemented in the array */
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	/* Cycle to next index by incrementing the array */
	auto NextIndex = (Index + 1) % PatrolPoints.Num();

	/* Set the next, incremented index value for next time this gets invoked */
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
