// Fill out your copyright notice in the Description page of Project Settings.

#include "Slinger.h"
#include "BirdBase.h"
#include <Components/CapsuleComponent.h>
#include <EnhancedInputComponent.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(Slinger, Log, All);

ASlinger::ASlinger()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(RootComponent);
}

void ASlinger::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(InputComponent);
	if (!eic)
	{
		UE_LOGFMT(Slinger, Error, "Could not cast to EnhancedInputComponent");
		return;
	}

	eic->BindAction(AimHoldAction, ETriggerEvent::Started, this, &ASlinger::OnAimStart);
	eic->BindAction(AimHoldAction, ETriggerEvent::Completed, this, &ASlinger::OnAimEnd);
	eic->BindAction(AimDirectionAction, ETriggerEvent::Triggered, this, &ASlinger::OnAimDirection);
	eic->BindAction(AimForceAction, ETriggerEvent::Triggered, this, &ASlinger::OnAimForce);
}

void ASlinger::OnAimStart()
{
	if (SpawnedBird)
	{
		UE_LOGFMT(Slinger, Error, "Already aiming");
		return;
	}

	if (Birds.IsEmpty())
	{
		UE_LOGFMT(Slinger, Error, "No bird");
		return;
	}

	auto& thisTransform = SpawnPoint->GetComponentTransform();
	FVector spawnLoc = thisTransform.GetLocation() - thisTransform.GetUnitAxis(EAxis::Y) * DistanceClamp.X;

	SpawnedBird = GetWorld()->SpawnActor<ABirdBase>(Birds[0], spawnLoc, thisTransform.GetRotation().Rotator());
	SpawnedBird->GetCapsuleComponent()->SetSimulatePhysics(false);
}

void ASlinger::OnAimEnd()
{
	if (!SpawnedBird)
	{
		UE_LOGFMT(Slinger, Error, "Not aiming");
		return;
	}

	const FVector thisLoc = SpawnPoint->GetComponentLocation();
	const FVector birdLoc = SpawnedBird->GetActorLocation();
	const FVector diff = thisLoc - birdLoc;

	if (FMath::IsNearlyEqual(diff.SizeSquared(), FMath::Square(DistanceClamp.X), UE_DOUBLE_KINDA_SMALL_NUMBER))
	{
		SpawnedBird->Destroy();
		SpawnedBird = nullptr;
		return;
	}

	Birds.RemoveAt(0);
	SpawnedBird->GetCapsuleComponent()->SetSimulatePhysics(true);
	SpawnedBird->LaunchCharacter(diff * ForceMultiplier, true, true);
	SpawnedBird = nullptr;
}

void ASlinger::OnAimDirection(const FInputActionValue& value)
{
	if (!SpawnedBird)
		return;

	const auto direction = value.Get<FVector2D>();
	const FVector thisLoc = SpawnPoint->GetComponentLocation();
	const FVector birdLoc = SpawnedBird->GetActorLocation();
	const FQuat birdQuat = SpawnedBird->GetActorQuat();

	FVector dir; float len;
	(birdLoc - thisLoc).ToDirectionAndLength(dir, len);

	dir += birdQuat.GetRightVector() * direction.X;
	dir -= birdQuat.GetUpVector() * direction.Y;

	const FVector newBirdLoc = thisLoc + dir.GetSafeNormal() * len;
	const FQuat newBirdQuat = FRotationMatrix::MakeFromXZ(-dir, SpawnPoint->GetUpVector()).ToQuat();

	SpawnedBird->SetActorLocation(newBirdLoc);
	SpawnedBird->SetActorRotation(newBirdQuat);
}

void ASlinger::OnAimForce(const FInputActionValue& value)
{
	if (!SpawnedBird)
		return;

	const auto force = value.Get<float>();
	const FVector thisLoc = SpawnPoint->GetComponentLocation();
	const FVector birdLoc = SpawnedBird->GetActorLocation();

	FVector dir; float len;
	(birdLoc - thisLoc).ToDirectionAndLength(dir, len);
	len = FMath::Clamp(len + force, DistanceClamp.X, DistanceClamp.Y);

	const FVector newBirdLoc = thisLoc + dir * len;
	SpawnedBird->SetActorLocation(newBirdLoc);
}
