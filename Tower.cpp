// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!Tank) return;
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	// TODO: make turret swivel when no target
	if (Distance > FireRange) return;
	RotateTurret(Tank->GetActorLocation());
	
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
