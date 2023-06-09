// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

class AToonTanksPlayerController;
class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	/* create widgets, etc with blueprints */
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	/* create widgets, etc with blueprints */
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	ATank* Tank;

	AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	int32 TargetTowers = 0;

	void HandleGameStart();

	int32 GetTargetTowersCount();
};
