

#pragma once

#include "GameFramework/Actor.h"
#include "CastleDoorActor.generated.h"

UCLASS()
class DYC_API ACastleDoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACastleDoorActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
