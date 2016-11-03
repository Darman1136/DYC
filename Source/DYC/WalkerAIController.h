

#pragma once

#include "AIController.h"
#include "WalkerAICharacter.h"
#include "AIWaypoint.h"
#include "IGrabableActor.h"
#include "TypesT.h"
#include "WalkerAIController.generated.h"

/**
 * 
 */
UCLASS()
class DYC_API AWalkerAIController : public AAIController
{
	GENERATED_BODY()

	AWalkerAIController(const class FObjectInitializer& ObjectInitializer);

	/* Called whenever the controller possesses a character bot */
	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;

	UBehaviorTreeComponent* BehaviorComp;

	UBehaviorTree* DefaultBehaviorTree;

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetEnemyKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PatrolLocationKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName CurrentWaypointKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BotTypeKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName AttackDoorName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName IsFallingName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName WasFallingName;

public:

	AAIWaypoint* GetBlackboardWaypoint();

	ACastleDoorDestructibleActor* GetBlackboardAttackDoor();

	void SetBlackboardWaypoint(AAIWaypoint* NewWaypoint);

	void SetBlackboardTargetEnemy(APawn* NewTarget);

	void SetBlackboardBotType(EBotBehaviorType NewType);

	void SetBlackboardAttackDoor(ACastleDoorDestructibleActor* NewDoor);

	void SetBlackboardIsFalling(bool IsFalling);

	void SetBlackboardWasFalling(bool WasFalling);

	FName GetBlackboardAttackDoorName();

	void OnDeath();
};
