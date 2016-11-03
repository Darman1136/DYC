

#include "DYC.h"
#include "BTTAttackDoor.h"
#include "WalkerAIController.h"
#include "CastleDoorDestructibleActor.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTAttackDoor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AWalkerAIController* AIController = Cast<AWalkerAIController>(OwnerComp.GetAIOwner());
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ACastleDoorDestructibleActor* AttackDoor = AIController->GetBlackboardAttackDoor();
	if (AttackDoor) {
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);
		AttackDoor->TakeDamage(10.f, DamageEvent, AIController, AIController->GetPawn());

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Apply Damage " + AIController->GetPawn()->GetName());
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
