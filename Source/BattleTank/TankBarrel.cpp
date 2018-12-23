// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	auto speed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedElevation = FMath::Clamp(RawNewElevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}


void UTankBarrel::Move(FRotator DeltaRotator) {

	Elevate(DeltaRotator.Pitch);
}