// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	UE_LOG(LogTemp, Warning, TEXT("Tower::HandleDestruction"));
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::TryFire, FireRate, true);
}

void ATower::TryFire()
{
	if (!IsInRange()) return;
	Fire();
}

bool ATower::IsInRange() const
{
	if (!Tank) return false;
	if (FireRange < FVector::Dist(GetActorLocation(), Tank->GetActorLocation())) return false;
	return true;
}
