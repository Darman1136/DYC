

#include "DYC.h"
#include "AISpawner.h"


// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnCounter = 0;
}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	if (ValidVariableSettings()) {
		BeginSpawning();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, this->GetClass()->GetName() + "--> Variable not set");
	}
}

// Called every frame
/*void AAISpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}*/


void AAISpawner::BeginSpawning() {
	if (SpawnTimerHandle.IsValid() == false) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Start Timer");
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAISpawner::SpawnAI, SpawnDelay, true);
	}
}

void AAISpawner::SpawnAI() {
	if (SpawnCounter < SpawnAmount) {
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AWalkerAICharacter* Actor = World->SpawnActor<AWalkerAICharacter>(CharacterToSpawnClass, GetActorLocation(), GetActorRotation(), SpawnParams);
			if (Actor) {
				AWalkerAIController* AIController = Cast<AWalkerAIController>(Actor->GetController());
				SpawnCounter++;
			}
		}
	}
	else {
		if (SpawnTimerHandle.IsValid()) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Stop spawning, reached limit");
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		}
	}
}

bool AAISpawner::ValidVariableSettings()
{
	if (CharacterToSpawnClass != NULL) {
		return true;
	}
	return false;
}