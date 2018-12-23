// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public: 

	void Move(FRotator DeltaRotator);
	
private:
	void Elevate(float RelatvieSpeed);
	void Rotate(float RelativeSpeed);

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegree = 30.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegree = 0.f;
};
