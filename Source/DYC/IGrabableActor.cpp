

#include "DYC.h"
#include "IGrabableActor.h"


// Sets default values
AIGrabableActor::AIGrabableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIGrabableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGrabableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

