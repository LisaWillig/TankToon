// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "AIController.h"
#include "TankTrack.h"

UTankMovementComponent::UTankMovementComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet) {
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throttle) {
	
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);

}

void UTankMovementComponent::IntendTurnRight(float Throttle) {

	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(-Throttle);

}

void UTankMovementComponent::IntendTurnLeft(float Throttle) {

	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(-Throttle);
	RightTrack->SetThrottle(Throttle);

}
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto MovementValue = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RotationValue = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	
	IntendMoveForward(MovementValue);
	IntendTurnRight(RotationValue);
}