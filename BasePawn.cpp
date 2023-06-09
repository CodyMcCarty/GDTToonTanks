// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DestructionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DestructionEffect, GetActorLocation(), GetActorRotation());
	}
	if (DeathCameraShakeClass)
	{
		UGameplayStatics::PlayWorldCameraShake(this, DeathCameraShakeClass, GetActorLocation(), 0.f, 5000.f);
	}
}

void ABasePawn::RotateTurret(const FVector& PointOfAim) const
{
	if (PointOfAim == FVector::ZeroVector) return;

	const FVector TurretToTarget = PointOfAim - TurretMesh->GetComponentLocation();
	//TODO: allow some pitch, may not always be flat map
	const FRotator SearchTraverse = FRotator(0.f, TurretToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), SearchTraverse,
	                                              UGameplayStatics::GetWorldDeltaSeconds(this), 10.f));
}

void ABasePawn::Fire()
{
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
	                                                      ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}
