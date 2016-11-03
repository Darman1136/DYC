

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "WalkerAIController.h"
#include "AIWaypoint.h"
#include "BTTFindNearestWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class DYC_API UBTTFindNearestWaypoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type UBTTFindNearestWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
