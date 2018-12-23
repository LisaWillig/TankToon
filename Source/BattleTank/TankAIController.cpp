// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "AimingComponent.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AIControlledTank = GetPawn();

	if (!ensure(PlayerTank &&AIControlledTank)) {return;}

	//TODO: acceptance radius adaption in bluprint (read only)
	//TODO: Make the tanks move...
	MoveToActor(PlayerTank, AcceptanceRadius);
	
	auto AimingComponent = AIControlledTank->FindComponentByClass<UAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringStatus::Locked) {
		
		AimingComponent->Fire();
	}
		
}




