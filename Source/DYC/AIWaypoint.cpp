

#include "DYC.h"
#include "AIWaypoint.h"


// Sets default values
AAIWaypoint::AAIWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIWaypoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

AAIWaypoint* AAIWaypoint::GetNextRandomWaypoint()
{
	if (Waypoints.Num() > 0) {
		int FirstWaypointIndex = FMath::RandRange(0, Waypoints.Num() - 1);
		if (Waypoints[FirstWaypointIndex]) {
			return Waypoints[FirstWaypointIndex];
		}
	}
	return nullptr;
}

ACastleDoorDestructibleActor* AAIWaypoint::GetAttackDoor()
{
	if (AttackDoor)
	{
		return AttackDoor;
	}
	return nullptr;
}
