

#include "DYC.h"
#include "GrabableCharacter.h"


// Sets default values
AGrabableCharacter::AGrabableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrabableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrabableCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AGrabableCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

