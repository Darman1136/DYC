

#include "DYC.h"
#include "BTTApplyFallDamage.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTApplyFallDamage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AWalkerAIController* AIController = Cast<AWalkerAIController>(OwnerComp.GetAIOwner());
	if (AIController == nullptr) {
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = AIController->GetPawn();
	AWalkerAICharacter* AICharacter = Cast<AWalkerAICharacter>(Pawn);
	if (AICharacter) {
		float ZVelocity = AICharacter->GetZVelocity();
		if (FMath::Abs(ZVelocity) > AICharacter->GetFallDamageThreshold()) {
			float Damage = FMath::Abs(ZVelocity) / 40.f;
			TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
			FDamageEvent DamageEvent(ValidDamageTypeClass);
			AICharacter->TakeDamage(Damage, DamageEvent, AIController, AIController->GetPawn());
			GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Blue, "Applied falling damage.");	
		}
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

