

#include "DYC.h"
#include "CastleDoorActor.h"


// Sets default values
ACastleDoorActor::ACastleDoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACastleDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACastleDoorActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

