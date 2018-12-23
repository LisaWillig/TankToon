// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "AimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Reloading, 
	Aiming, 
	Locked,
	OutOfAmmo,
};


//Forward declaration 
class UTankBarrel; 
class UTankTurret; 
class AProjectile;

//Hold Barrels Properties and Elevate method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeAiming(UTankBarrel* Barrel, UTankTurret* Turret);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 40000;
	double LastFireTime = 0;
	void MoveBarrel(FVector AimDirection);
	bool IsBarrelMoving();
	UFUNCTION(BlueprintCallable, Category = "Fire")
	int32 GetRoundsLeft() const; 
	EFiringStatus GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:

	// Sets default values for this component's properties
	UAimingComponent();

	UTankBarrel * Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3;

	FVector AimDirection = { 0,0,0 };

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};