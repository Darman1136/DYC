

#pragma once

#include "GameFramework/PlayerController.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "VRPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DYC_API AVRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AVRPlayerController(const class FObjectInitializer& ObjectInitializer);
	
	
};
