// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed) {
	auto speed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

void UTankTurret::Move(FRotator DeltaRotator) {

	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Rotate(DeltaRotator.Yaw);
	}
	else {
		Rotate(-DeltaRotator.Yaw);
	}
}
