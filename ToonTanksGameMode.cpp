// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (Tank->GetTankPlayerController())
		{
			// Tank->DisableInput(Tank->GetTankPlayerController());
			// Tank->GetTankPlayerController()->bShowMouseCursor = false;
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("TTGM:DestroyedTower"));
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
