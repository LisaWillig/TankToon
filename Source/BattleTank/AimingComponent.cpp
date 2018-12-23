// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "BattleTank.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	if (RoundsLeft <= 0) {
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}

bool UAimingComponent::IsBarrelMoving() {

	if (!ensure(Barrel)) { return false; }
	FVector Origin = Barrel->GetForwardVector();
	return Origin.Equals(AimDirection, 0.1);
}

void UAimingComponent::InitializeAiming(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

int32 UAimingComponent::GetRoundsLeft() const {
	return RoundsLeft;
}
void UAimingComponent::AimAt(FVector HitLocation){
	if (!ensure(Barrel)) {return;};

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = false;

	bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		0,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		//The rest is optional
	    );

	if(bHaveAimSolution){
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	};

}

void UAimingComponent::MoveBarrel(FVector AimDirection) {
	if (!ensure(Barrel && Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator; 
	Barrel->Move(DeltaRotator);
	Turret->Rotate(DeltaRotator.Yaw);

}

EFiringStatus UAimingComponent::GetFiringState() const {
	return FiringStatus;
}

void UAimingComponent::Fire() {

	if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming) {
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }

		bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

		if (Barrel && isReloaded) {

			auto SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
			auto SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);

			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
			RoundsLeft--;
		}
	}
}

