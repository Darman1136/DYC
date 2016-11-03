// Fill out your copyright notice in the Description page of Project Settings.

#include "DYC.h"
#include "VRPawn.h"


// Sets default values
AVRPawn::AVRPawn(const class FObjectInitializer& PCIP)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsHandleGrabbed = false;
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	BaseEyeHeight = 0.f;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	RootComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	CapsuleComponent = PCIP.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("CapsuleComponent"));
	if (CapsuleComponent)
	{
		CapsuleComponent->SetCapsuleHalfHeight(96.f);
		CapsuleComponent->SetCapsuleRadius(16.f);
	}

	SceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	if (SceneComponent)
	{
		SceneComponent->SetRelativeLocation(FVector(0.f,0.f,-100.f));
	}

	CameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraComponent"));
	if (SceneComponent && CameraComponent)
	{
		CameraComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepWorldTransform);
	}

	SteamVRChaperoneComponent = PCIP.CreateDefaultSubobject<USteamVRChaperoneComponent>(this, TEXT("SteamVRChaperoneComponent"));

	LeftMotionControllerComponent = PCIP.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("LeftMotionControllerComponent"));
	if (LeftMotionControllerComponent)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> FoundLeftMotionController(TEXT("/Game/Assets/VR/Vive/Controllers/Vive_Controller_V2_Mesh.Vive_Controller_V2_Mesh"));
		if (FoundLeftMotionController.Succeeded()) 
		{
			SMLeftMotionController = FoundLeftMotionController.Object;

			LeftMotionControllerStaticMeshComponent = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("LeftMotionControllerStaticMeshComponent"));
			if (LeftMotionControllerStaticMeshComponent)
			{
				LeftMotionControllerStaticMeshComponent->AttachToComponent(LeftMotionControllerComponent, FAttachmentTransformRules::KeepWorldTransform);
				LeftMotionControllerStaticMeshComponent->SetStaticMesh(SMLeftMotionController);
				LeftMotionControllerStaticMeshComponent->SetRelativeScale3D(FVector(15.f, 15.f, 15.f));

				LeftCollisionSphereComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("LeftCollisionSphereComponent"));
				if (LeftCollisionSphereComponent)
				{
					LeftCollisionSphereComponent->SetSphereRadius(20000.f);
					LeftCollisionSphereComponent->AttachToComponent(LeftMotionControllerStaticMeshComponent, FAttachmentTransformRules::KeepWorldTransform);
				}

				LeftMotionControllerComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}

	RightMotionControllerComponent = PCIP.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("RightMotionControllerComponent"));
	if (RightMotionControllerComponent) 
	{
		RightMotionControllerComponent->Hand = EControllerHand::Right;
		static ConstructorHelpers::FObjectFinder<UStaticMesh> FoundRightMotionController(TEXT("/Game/Assets/VR/Vive/Controllers/Vive_Controller_V2_Mesh.Vive_Controller_V2_Mesh"));
		if (FoundRightMotionController.Succeeded()) 
		{
			SMRightMotionController = FoundRightMotionController.Object;

			RightMotionControllerStaticMeshComponent = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("RightMotionControllerStaticMeshComponent"));
			if (RightMotionControllerStaticMeshComponent)
			{
				RightMotionControllerStaticMeshComponent->AttachToComponent(RightMotionControllerComponent, FAttachmentTransformRules::KeepWorldTransform);
				RightMotionControllerStaticMeshComponent->SetStaticMesh(SMRightMotionController);
				RightMotionControllerStaticMeshComponent->SetRelativeScale3D(FVector(15.f, 15.f, 15.f));

				RightCollisionSphereComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("RightCollisionSphereComponent"));
				if (RightCollisionSphereComponent)
				{
					RightCollisionSphereComponent->SetSphereRadius(20000.f);
					RightCollisionSphereComponent->AttachToComponent(RightMotionControllerStaticMeshComponent, FAttachmentTransformRules::KeepWorldTransform);
				}

				RightMotionControllerComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}

	PhysicsHandleComponent = PCIP.CreateDefaultSubobject<UPhysicsHandleComponent>(this, TEXT("PhysicsHandleComponent"));
	
	if (PhysicsHandleComponent)
	{

		//FConstraintInstance PhysicsConstraintInstance;
		//PhysicsConstraintComponent->ConstraintInstance = PhysicsConstraintInstance;
		//PhysicsHandleComponent->AttachToComponent(LeftMotionControllerStaticMeshComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("" + GetController()->GetClass()->GetName()));
}

// Called every frame
void AVRPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (PhysicsHandleGrabbed)
	{
		FVector NewLoc = LeftMotionControllerStaticMeshComponent->GetSocketLocation("GrabPoint");
		PhysicsHandleComponent->SetTargetLocation(NewLoc);
	}
}

AActor* AVRPawn::GetClosestLeftCollidingActor()
{
	TArray<AActor*> OverlappingActors;
	LeftCollisionSphereComponent->GetOverlappingActors(OverlappingActors, AGrabableCharacter::StaticClass());
	return GetClosestActor(LeftCollisionSphereComponent, OverlappingActors);
}

AActor* AVRPawn::GetClosestRightCollidingActor()
{
	TArray<AActor*> OverlappingActors;
	RightCollisionSphereComponent->GetOverlappingActors(OverlappingActors, AGrabableCharacter::StaticClass());
	return GetClosestActor(RightCollisionSphereComponent, OverlappingActors);
}

AActor* AVRPawn::GetClosestActor(USphereComponent* CollisionSphere, TArray<AActor*>& Actors)
{
	float SmallestDistance = 9999999;
	AActor* ClosestActor = nullptr;
	for (size_t i = 0; i < Actors.Num(); i++)
	{
		float CurrentDistance = (CollisionSphere->GetComponentLocation() - Actors[i]->GetActorLocation()).Size();
		if (SmallestDistance > CurrentDistance)
		{
			SmallestDistance = CurrentDistance;
			ClosestActor = Actors[i];
		}
	}
	return ClosestActor;
}


template<EControllerHand Hand>
void AVRPawn::OnTrigger()
{
	AActor* ClosestActor;
	if (Hand == EControllerHand::Left)
	{
		ClosestActor = GetClosestLeftCollidingActor();
		Log(FString("Pressed: Left Trigger"));
	}
	else
	{
		ClosestActor = GetClosestRightCollidingActor();
		Log(FString("Pressed: Right Trigger"));
	}

	if (ClosestActor)
	{
		AGrabableCharacter* GrabableCharacter = Cast<AGrabableCharacter>(ClosestActor);
		if (GrabableCharacter)
		{
			
			USkeletalMeshComponent* GrabableCharacterMesh = GrabableCharacter->GetMesh();
			if (Hand == EControllerHand::Left)
			{
				if (!PhysicsHandleGrabbed) 
				{
					GrabableCharacterMesh->SetSimulatePhysics(true);
					 //set is grabbed in walker ai und im bt tree
					PhysicsHandleComponent->GrabComponent(GrabableCharacter->GetMesh(), NAME_None, GrabableCharacter->GetActorLocation(), false);
					GrabbedActorMesh = GrabableCharacterMesh;
					PhysicsHandleGrabbed = true;
				} 
				else
				{
					GrabbedActorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					PhysicsHandleComponent->ReleaseComponent();
					PhysicsHandleGrabbed = false;
					GrabbedActorMesh = nullptr;
				}
				//PhysicsConstraintComponent->SetConstrainedComponents(LeftMotionControllerStaticMeshComponent, NAME_None, GrabableCharacterMesh, NAME_None);
				//GrabableCharacterMesh->AttachTo(LeftMotionControllerComponent, FName("GrabPoint"), EAttachLocation::SnapToTarget, false);
			}
			else
			{
				//GrabableCharacterMesh->AttachTo(RightMotionControllerComponent, FName("GrabPoint"), EAttachLocation::SnapToTarget, false);
			}
		}
	}
}


void AVRPawn::Touch3()
{
	GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Red, TEXT("Pressed 3"));
}

void AVRPawn::Touch4()
{
	GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Red, TEXT("Pressed 4"));
}

void AVRPawn::Touch5()
{
	GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Red, TEXT("Pressed 5"));
}

void AVRPawn::Touch6()
{
	GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Red, TEXT("Pressed 6"));
}

void AVRPawn::Touch7()
{
	GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Red, TEXT("Pressed 7"));

}
// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Red, TEXT("setup"));
	InputComponent->BindAction("LeftTrigger", IE_Pressed, this, &AVRPawn::OnTrigger<EControllerHand::Left>);
	InputComponent->BindAction("RightTrigger", IE_Pressed, this, &AVRPawn::OnTrigger<EControllerHand::Right>);
	InputComponent->BindAction("Touch3", IE_Pressed, this, &AVRPawn::Touch3);
	InputComponent->BindAction("Touch4", IE_Pressed, this, &AVRPawn::Touch4);
	InputComponent->BindAction("Touch5", IE_Pressed, this, &AVRPawn::Touch5);
	InputComponent->BindAction("Touch6", IE_Pressed, this, &AVRPawn::Touch6);
	InputComponent->BindAction("Touch7", IE_Pressed, this, &AVRPawn::Touch7);
}

void AVRPawn::Log(const FString& Text) {
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, Text);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), FName(*Text).ToString());
}