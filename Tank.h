// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	;
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	;
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	float Speed = 1200.f;

	UPROPERTY(EditAnywhere)
	float TurnRate = 200.f;

	APlayerController* PlayerControllerRef;

	void Move(float Value);

	void Turn(float Value);
};
