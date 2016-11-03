

#include "DYC.h"
#include "CastleDoorDestructibleActor.h"

void ACastleDoorDestructibleActor::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	DamageStage = 0;
}


float ACastleDoorDestructibleActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float AbsoluteDamage = Super::TakeDamage(Damage,DamageEvent, EventInstigator, DamageCauser);

	Health -= AbsoluteDamage;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "HP: " + FString::SanitizeFloat(Health));
	if (Health < 0) {
		Health = 0;
		if (DamageStage == 2) {
			DamageDestructibleMesh(1000.f, 0.f);
			DoorDestroyed();
			DamageStage++;
		}
	}

	float ZOffset = 0.f;
	if (DamageStage == 1 && MaxHealth * 0.25 > Health) {
		ZOffset = 250.f;
		DamageDestructibleMesh(3.f, ZOffset);
		DamageStage++;
	}
	if (DamageStage == 0 && MaxHealth * 0.5 > Health) {
		ZOffset = 100.f;
		DamageDestructibleMesh(3.f, ZOffset);
		DamageStage++;
	}
	
	return AbsoluteDamage;
}

void ACastleDoorDestructibleActor::DamageDestructibleMesh(float Damage, float ZOffset)
{
	GetDestructibleComponent()->ApplyDamage(Damage, GetActorLocation() + FVector(0, 0, ZOffset), GetActorForwardVector(), 50000.f);
}

void ACastleDoorDestructibleActor::DoorDestroyed() {
	bIsDestroyed = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Door destroyed");
}

bool ACastleDoorDestructibleActor::IsDestroyed() {
	return bIsDestroyed;
}