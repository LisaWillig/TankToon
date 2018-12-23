// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "TankPlayerController.generated.h"

class UAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UAimingComponent* AimCompRef);


private:
	void AimTowardsCrosshair();
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f; 
 


	FVector* HitLocation;
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(FVector2D, FVector&) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;
	virtual void Tick(float DeltaTime) override; 
	void BeginPlay() override; 

	/*Please make sure there is something else up the inheritance hierachy with exactly this signature
		if virtual method was declared originally (in this case: virtual beginPlay) functon can be overriden by any ancestor in the future
		declare virtual on a virtual function: does nothing, it stays virtual*/
	/*Override a virual method:
		find signature in API reference
		copy signature, postfix "override" in the header file
		define in cpp without virtual or override*/
};
