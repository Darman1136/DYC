

#include "DYC.h"
#include "BTTFindNextWaypoint.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTFindNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AWalkerAIController* AIController = Cast<AWalkerAIController>(OwnerComp.GetAIOwner());
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AAIWaypoint* CurrentWaypoint = AIController->GetBlackboardWaypoint();
	AActor* NewWaypoint = nullptr;

	/* Set next waypoint from the current one */
	NewWaypoint = CurrentWaypoint->GetNextRandomWaypoint();

	/* Iterate all the bot waypoints in the current level and find a new random waypoint to set as destination */
	//TArray<AActor*> AllWaypoints;
	//UGameplayStatics::GetAllActorsOfClass(MyController, AAIWaypoint::StaticClass(), AllWaypoints);

	//if (AllWaypoints.Num() == 0)
	//	return EBTNodeResult::Failed;

	/* Find a new waypoint randomly by index (this can include the current waypoint) */
	/* For more complex or human AI you could add some weights based on distance and other environmental conditions here */
	//NewWaypoint = AllWaypoints[FMath::RandRange(0, AllWaypoints.Num() - 1)];

	/* Assign the new waypoint to the Blackboard */
	if (NewWaypoint)
	{
		/* The selected key should be "CurrentWaypoint" in the BehaviorTree setup */
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), NewWaypoint);
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(AIController->GetBlackboardAttackDoorName(), nullptr);
	}
	else
	{
		ACastleDoorDestructibleActor* AttackDoor = CurrentWaypoint->GetAttackDoor();
		if (AttackDoor)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(AIController->GetBlackboardAttackDoorName(), AttackDoor);
		}
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), nullptr);
	}
		return EBTNodeResult::Succeeded;
}
