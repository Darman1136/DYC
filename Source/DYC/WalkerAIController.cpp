

#include "DYC.h"
#include "WalkerAIController.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AWalkerAIController::AWalkerAIController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	/* Match with the AI/ZombieBlackboard */
	PatrolLocationKeyName = "PatrolLocation";
	CurrentWaypointKeyName = "NextWaypoint";
	BotTypeKeyName = "BotType";
	TargetEnemyKeyName = "TargetEnemy";
	AttackDoorName = "AttackDoor";
	IsFallingName = "IsFalling";
	WasFallingName = "WasFalling";

	/* Initializes PlayerState so we can assign a team index to AI */
	bWantsPlayerState = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTOb(TEXT("BehaviorTree'/Game/AI/Walker/BTWalker.BTWalker'"));
	DefaultBehaviorTree = BTOb.Object;
}


void AWalkerAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	AWalkerAICharacter* walker = Cast<AWalkerAICharacter>(InPawn);
	if (walker)
	{
		if (walker->BehaviorTree) {
			if (walker->BehaviorTree->BlackboardAsset)
			{
				BlackboardComp->InitializeBlackboard(*walker->BehaviorTree->BlackboardAsset);

				/* Make sure the Blackboard has the type of bot we possessed */
				SetBlackboardBotType(walker->BotType);
				SetBlackboardIsFalling(true);
				SetBlackboardWasFalling(true);
			}

			BehaviorComp->StartTree(*walker->BehaviorTree);
		}
		else {
			if (DefaultBehaviorTree->BlackboardAsset)
			{
				BlackboardComp->InitializeBlackboard(*DefaultBehaviorTree->BlackboardAsset);

				/* Make sure the Blackboard has the type of bot we possessed */
				SetBlackboardBotType(walker->BotType);
				SetBlackboardIsFalling(true);
				SetBlackboardWasFalling(true);
			}

			BehaviorComp->StartTree(*DefaultBehaviorTree);
		}
	}	
}


void AWalkerAIController::UnPossess()
{
	Super::UnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}


void AWalkerAIController::SetBlackboardWaypoint(AAIWaypoint* NewWaypoint)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(CurrentWaypointKeyName, NewWaypoint);
	}
}


void AWalkerAIController::SetBlackboardTargetEnemy(APawn* NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, NewTarget);
	}
}


AAIWaypoint* AWalkerAIController::GetBlackboardWaypoint()
{
	if (BlackboardComp)
	{
		return Cast<AAIWaypoint>(BlackboardComp->GetValueAsObject(CurrentWaypointKeyName));
	}

	return nullptr;
}

void AWalkerAIController::SetBlackboardBotType(EBotBehaviorType NewType)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(BotTypeKeyName, (uint8)NewType);
	}
}

void AWalkerAIController::SetBlackboardAttackDoor(ACastleDoorDestructibleActor* NewDoor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(AttackDoorName, NewDoor);
	}
}

ACastleDoorDestructibleActor* AWalkerAIController::GetBlackboardAttackDoor()
{
	if (BlackboardComp)
	{
		return Cast<ACastleDoorDestructibleActor>(BlackboardComp->GetValueAsObject(AttackDoorName));
	}

	return nullptr;
}

void AWalkerAIController::SetBlackboardIsFalling(bool IsFalling)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsFallingName, IsFalling);
	}
}

void AWalkerAIController::SetBlackboardWasFalling(bool WasFalling)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(WasFallingName, WasFalling);
	}
}

FName AWalkerAIController::GetBlackboardAttackDoorName()
{
	return AttackDoorName;
}

void AWalkerAIController::OnDeath()
{
	if (BehaviorComp) {
		BehaviorComp->StopTree();
	}
}
 