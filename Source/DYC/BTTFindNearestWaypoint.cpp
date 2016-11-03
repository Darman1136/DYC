

#include "DYC.h"
#include "BTTFindNearestWaypoint.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTFindNearestWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AWalkerAIController* AIController = Cast<AWalkerAIController>(OwnerComp.GetAIOwner());
	if (AIController == nullptr) {
		return EBTNodeResult::Failed;
	}
	
	TArray<AActor*> AllWaypoints;
	UGameplayStatics::GetAllActorsOfClass(AIController, AAIWaypoint::StaticClass(), AllWaypoints);

	if (AllWaypoints.Num() == 0) {
		return EBTNodeResult::Failed;
	}

	float ShortestDistance = 99999999.f;
	AAIWaypoint* NewWaypoint = nullptr;
	APawn* Pawn = AIController->GetPawn();
	for (AActor* Waypoint : AllWaypoints) {
		float Distance = (Pawn->GetActorLocation() - Waypoint->GetActorLocation()).Size();
		if (Distance < ShortestDistance) {
			NewWaypoint = Cast<AAIWaypoint>(Waypoint);
			ShortestDistance = Distance;
		}
	}
	
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), NewWaypoint);
	AIController->SetBlackboardWasFalling(false);
	GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Yellow, "Found new waypoint after falling");
	return EBTNodeResult::Succeeded;
}

