

#include "DYC.h"
#include "WalkerAICharacter.h"
#include "WalkerAIController.h"
#include "AIWaypoint.h"

AWalkerAICharacter::AWalkerAICharacter(const class FObjectInitializer& ObjectInitializer)
	: Super()
{
	AIControllerClass = AWalkerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//Timeline setup for dissolve on death
	static  ConstructorHelpers::FObjectFinder<UCurveFloat> FoundDissolveCurve(TEXT("/Game/Assets/Timelines/AIPhaseOutCurve.AIPhaseOutCurve"));
	if (FoundDissolveCurve.Succeeded()) {
		DissolveCurve = FoundDissolveCurve.Object;
	}
	DissolveTimelineComponent = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("DissolveTimelineComponent"));
	DissolveInterpFunction.BindUFunction(this, FName{ TEXT("DissolveProgress") });

	static  ConstructorHelpers::FObjectFinder<UMaterial> FoundDissolveMaterial(TEXT("/Game/Assets/Meshs/Mannequin/Materials/M_UE4Man_Body_Dissolvable.M_UE4Man_Body_Dissolvable"));
	if (FoundDissolveMaterial.Succeeded()) {
		DissolveMaterial = FoundDissolveMaterial.Object;
	}
	DissolveMaterialParamName = "Dissolve";

	IS_FALLING_CHECK_DELAY = .05f;
	BEFORE_ACTOR_DESTROY_DELAY = 10.f;
	BEFORE_ACTOR_DISSOLVE_DELAY = 5.f;

	Health = MaxHealth;
}


void AWalkerAICharacter::BeginPlay()
{
	Super::BeginPlay();

	DissolveTimelineComponent->AddInterpFloat(DissolveCurve, DissolveInterpFunction, FName{ TEXT("Dissolve") });
	DissolveMaterialInstanceDynamic = GetMesh()->CreateDynamicMaterialInstance(0, DissolveMaterial);

	if (IsFallingTimerHandle.IsValid() == false) {
		GetWorldTimerManager().SetTimer(IsFallingTimerHandle, this, &AWalkerAICharacter::CheckIfIsFalling, IS_FALLING_CHECK_DELAY, true);
	}
}


void AWalkerAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);		
}

void AWalkerAICharacter::CheckIfIsFalling()
{
	AWalkerAIController* AIController = Cast<AWalkerAIController>(GetController());
	if (!AIController->GetPawn()->GetMovementComponent()->IsFalling() || FMath::Abs(GetVelocity().Z) < 5) {
		//GetMesh()->SetSimulatePhysics(false);
		//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AIController->SetBlackboardIsFalling(false);
		//GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		//GetMesh()->SetSimulatePhysics(true);
		//LaunchCharacter(FVector(12.f, 0.f, 10000.f), true, true);
	}
	else {
		ZVelocity = GetVelocity().Z;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "ZVel: " + FString::SanitizeFloat(ZVelocity));
		AIController->SetBlackboardIsFalling(true);
		AIController->SetBlackboardWasFalling(true);
	}
}

float AWalkerAICharacter::GetZVelocity() {
	return ZVelocity;
}

float AWalkerAICharacter::GetFallDamageThreshold() {
	return FallDamageThreshold;
}

bool AWalkerAICharacter::IsAlive() {
	return Health > 0;
}

float AWalkerAICharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float AbsoluteDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Health -= AbsoluteDamage;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "HP: " + FString::SanitizeFloat(Health) +" "+ this->GetName());
	if (Health < 0) {
		Health = 0;
		OnDeath();
	}

	return AbsoluteDamage;
}

void AWalkerAICharacter::OnDeath() {
	AWalkerAIController* AIController = Cast<AWalkerAIController>(GetController());
	if (AIController) {
		AIController->OnDeath();
	}
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Died " + this->GetName());

	if (!DissolveOnDeathTimerHandle.IsValid()) {
		GetWorldTimerManager().SetTimer(DissolveOnDeathTimerHandle, this, &AWalkerAICharacter::StartDissolveOnDeath, BEFORE_ACTOR_DISSOLVE_DELAY, false);
	}
	if (!DestroyActorTimerHandle.IsValid()) {
		GetWorldTimerManager().SetTimer(DestroyActorTimerHandle, this, &AWalkerAICharacter::DestroyActorOnDeath, BEFORE_ACTOR_DESTROY_DELAY, false);
	}
}

void AWalkerAICharacter::StartDissolveOnDeath()
{
	if (DissolveTimelineComponent) {
		DissolveTimelineComponent->PlayFromStart();
	}
}

void AWalkerAICharacter::DestroyActorOnDeath()
{
	Destroy();
}

void AWalkerAICharacter::DissolveProgress(float Value)
{
	DissolveMaterialInstanceDynamic->SetScalarParameterValue(DissolveMaterialParamName, Value);
}