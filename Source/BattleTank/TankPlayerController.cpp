// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "AimingComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	if (!AimingComponent) {return;}
	FoundAimingComponent(AimingComponent);
	
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetPawn()) { return;  }
	auto AimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; //OutParameter
	if (GetSightRayHitLocation(HitLocation)){
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)const {

	//find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, HitLocation);
	};
	return true; 
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const{
	
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = StartLocation + (LookDirection * LineTraceRange);
	FHitResult HitResult;
	bool HitSomething;
	
	HitSomething = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		LineTraceEnd,
		ECollisionChannel(ECC_Visibility)
	);
	if (HitSomething) {
		HitLocation = HitResult.Location;
		return true;
	}
	else { 
		HitLocation = FVector(0); 
		return false; }

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
	FVector CameraLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection);
	return true; 
}