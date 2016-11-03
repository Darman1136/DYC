// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "VRPawn.h"
#include "VRPlayerController.h"
#include "DYCGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DYC_API ADYCGameMode : public AGameMode
{
	GENERATED_BODY()

	ADYCGameMode(const FObjectInitializer& ObjectInitializer);
	
	virtual void StartPlay() override;
};
