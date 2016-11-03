

#pragma once

#include "GameFramework/Actor.h"
#include "CastleDoorDestructibleActor.h"
#include "AIWaypoint.generated.h"

UCLASS()
class DYC_API AAIWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIWaypoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	AAIWaypoint* GetNextRandomWaypoint();

	ACastleDoorDestructibleActor* GetAttackDoor();

private:
	UPROPERTY(EditAnywhere, Category = "Spawner")
		TArray<AAIWaypoint*> Waypoints;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		ACastleDoorDestructibleActor* AttackDoor;
};
