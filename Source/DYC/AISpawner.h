

#pragma once

#include "GameFramework/Actor.h"
#include "AIWaypoint.h"
#include "WalkerAICharacter.h"
#include "WalkerAIController.h"
#include "AISpawner.generated.h"

UCLASS()
class DYC_API AAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawner")
		TArray<AAIWaypoint*> Waypoints;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0), Category = "Spawner")
		float SpawnDelay;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0), Category = "Spawner")
		int SpawnAmount;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		TSubclassOf<class AWalkerAICharacter> CharacterToSpawnClass;

	int SpawnCounter;

	FTimerHandle SpawnTimerHandle;

	void BeginSpawning();
	 
	void SpawnAI();

	bool ValidVariableSettings();
};
