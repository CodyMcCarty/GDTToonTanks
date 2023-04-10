// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CheckFireCondition()) RotateTurret(Tank->GetActorLocation());
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::TryFire, FireRate, true);
}

void ATower::TryFire()
{
	if (!CheckFireCondition()) return;
	Fire();
}

bool ATower::CheckFireCondition() const
{
	if (!Tank) return false;
	const bool IsInRange = FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
	if (!IsInRange) return false;
	return true;
}
