

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "WalkerAIController.h"
#include "AIWaypoint.h"
#include "WalkerAICharacter.h"
#include "BTTApplyFallDamage.generated.h"

/**
 * 
 */
UCLASS()
class DYC_API UBTTApplyFallDamage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
