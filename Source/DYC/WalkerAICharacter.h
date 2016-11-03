

#pragma once

#include "GameFramework/Character.h"
#include "GrabableCharacter.h"
#include "TypesT.h"
#include "CastleDoorDestructibleActor.h"
#include "WalkerAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class DYC_API AWalkerAICharacter : public AGrabableCharacter
{
	GENERATED_BODY()
	/* Last time we attacked something */
	float LastMeleeAttackTime;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	AWalkerAICharacter(const class FObjectInitializer& ObjectInitializer);

	/* The bot behavior we want this bot to execute, (passive/patrol) by specifying EditAnywhere we can edit this value per-instance when placed on the map. */
	UPROPERTY(EditAnywhere, Category = "AI")
		EBotBehaviorType BotType;

	/* The thinking part of the brain, steers our zombie and makes decisions based on the data we feed it from the Blackboard */
	/* Assigned at the Character level (instead of Controller) so we may use different zombie behaviors while re-using one controller. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	bool IsAlive();

	float GetZVelocity();

	float GetFallDamageThreshold();

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	class ACastleDoorDestructibleActor* AttackDoor;

	UPROPERTY(EditAnywhere, Category = "AI")
		float FallDamageThreshold = 1000.f;

	UPROPERTY(EditAnywhere, Category = "AI")
		float MaxHealth = 100.f;

	UPROPERTY()
		UTimelineComponent* DissolveTimelineComponent;

	UPROPERTY()
		UCurveFloat* DissolveCurve;

	UPROPERTY()
		UMaterial* DissolveMaterial;

	UPROPERTY()
		UMaterialInstanceDynamic* DissolveMaterialInstanceDynamic;

	FOnTimelineFloat DissolveInterpFunction{};

	FTimerHandle IsFallingTimerHandle;

	FTimerHandle DestroyActorTimerHandle;

	FTimerHandle DissolveOnDeathTimerHandle;

	FName DissolveMaterialParamName;

	float IS_FALLING_CHECK_DELAY;

	float BEFORE_ACTOR_DISSOLVE_DELAY;

	float BEFORE_ACTOR_DESTROY_DELAY;

	float ZVelocity;

	float Health;
	
	void CheckIfIsFalling();

	void OnDeath();
	
	void DestroyActorOnDeath();

	void StartDissolveOnDeath();

	UFUNCTION()
	void DissolveProgress(float Value);
};
