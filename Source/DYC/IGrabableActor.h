

#pragma once

#include "GameFramework/Actor.h"
#include "IGrabableActor.generated.h"

UCLASS()
class DYC_API AIGrabableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGrabableActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
