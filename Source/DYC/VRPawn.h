// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "VRPlayerController.h"
#include "SteamVRChaperoneComponent.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "GrabableCharacter.h"
#include "PhysicsEngine/PhysicsConstraintActor.h"
#include "PhysicsEngine/PhysicsConstraintTemplate.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "VRPawn.generated.h"

UCLASS(Blueprintable)
class DYC_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	UInputComponent* InputComponent = nullptr;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
		UCameraComponent* CameraComponent;

	USteamVRChaperoneComponent* SteamVRChaperoneComponent;
	
	USkeletalMeshComponent* GrabbedActorMesh;
	bool PhysicsHandleGrabbed;
	UPROPERTY(EditAnywhere)
		UPhysicsHandleComponent* PhysicsHandleComponent;

	UPROPERTY(EditAnywhere)
		UMotionControllerComponent* LeftMotionControllerComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LeftMotionControllerStaticMeshComponent;
	UPROPERTY(EditAnywhere)
		USphereComponent* LeftCollisionSphereComponent;

	UPROPERTY(EditAnywhere)
		UMotionControllerComponent* RightMotionControllerComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RightMotionControllerStaticMeshComponent;
	UPROPERTY(EditAnywhere)
		USphereComponent* RightCollisionSphereComponent;

	AActor* GetClosestLeftCollidingActor();
	AActor* GetClosestRightCollidingActor();
	AActor* GetClosestActor(USphereComponent* CollisionSphere, TArray<AActor*>& Actors);

	template<EControllerHand Hand>
	void OnTrigger();

	void Touch3();
	void Touch4();
	void Touch5();
	void Touch6();
	void Touch7();

	UStaticMesh* SMLeftMotionController;
	UStaticMesh* SMRightMotionController;

	void Log(const FString& Text);
};
