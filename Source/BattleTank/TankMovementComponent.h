// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "AIController.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throttle);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throttle);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnLeft(float Throttle);

private:

	UTankMovementComponent();
	//called from pathfinding logic from AIController
	virtual void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	
	

};


