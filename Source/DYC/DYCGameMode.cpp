// Fill out your copyright notice in the Description page of Project Settings.

#include "DYC.h"
#include "DYCGameMode.h"


ADYCGameMode::ADYCGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = AVRPawn::StaticClass();
	PlayerControllerClass = AVRPlayerController::StaticClass();
}

void ADYCGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("GameMode started"));
	}
}