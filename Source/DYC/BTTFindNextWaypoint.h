

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "WalkerAIController.h"
#include "AIWaypoint.h"
#include "CastleDoorDestructibleActor.h"
#include "BTTFindNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class DYC_API UBTTFindNextWaypoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
