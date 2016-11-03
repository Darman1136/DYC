

#pragma once

#include "PhysicsEngine/DestructibleActor.h"
#include "CastleDoorDestructibleActor.generated.h"

/**
 * 
 */
UCLASS()
class DYC_API ACastleDoorDestructibleActor : public ADestructibleActor
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


private:
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0), Category = "General")
		float MaxHealth = 1000;

	float Health;

	bool bIsDestroyed;

	int DamageStage;
	
	void DamageDestructibleMesh(float Damage, float ZOffset);

	void DoorDestroyed();

	bool IsDestroyed();
};
