// Fill out your copyright notice in the Description page of Project Settings.

#include "Slinger.h"
#include "BirdBase.h"
#include <Components/CapsuleComponent.h>
#include <EnhancedInputComponent.h>
#include <Logging/StructuredLog.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SplineComponent.h>

DEFINE_LOG_CATEGORY_STATIC(Slinger, Log, All);

ASlinger::ASlinger()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
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

void ASlinger::Tick(float dt)
{
	Super::Tick(dt);

	if (!SpawnedBird)
	{
		UE_LOGFMT(Slinger, Error, "Tick called without bird");
		return;
	}


	const FVector thisLoc = SpawnPoint->GetComponentLocation();
	const FVector birdLoc = SpawnedBird->GetActorLocation();
	const FVector diff = thisLoc - birdLoc;
	const float speed = diff.Length();

	if (FMath::IsNearlyEqual(speed, DistanceClamp.X, UE_DOUBLE_KINDA_SMALL_NUMBER))
	{
		return;
	}

	FPredictProjectilePathParams predictParams(0.f, birdLoc, diff * ForceMultiplier, 10.f, ECC_Visibility, SpawnedBird);

	FPredictProjectilePathResult predictResult;
	UGameplayStatics::PredictProjectilePath(GetWorld(), predictParams, predictResult);

	SplineComponent->ClearSplinePoints(false);
	for (int32 i = 0; i < predictResult.PathData.Num(); ++i)
	{
		FVector location = predictResult.PathData[i].Location;
		SplineComponent->AddSplinePointAtIndex(location, i, ESplineCoordinateSpace::World, false);
	}

	SplineComponent->UpdateSpline();
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
	FVector spawnLoc = thisTransform.GetLocation() - thisTransform.GetUnitAxis(EAxis::X) * DistanceClamp.X;

	SpawnedBird = GetWorld()->SpawnActor<ABirdBase>(Birds[0], spawnLoc, thisTransform.GetRotation().Rotator());
	SetActorTickEnabled(true);
}

void ASlinger::OnAimEnd()
{
	if (!SpawnedBird)
	{
		UE_LOGFMT(Slinger, Error, "Not aiming");
		return;
	}

	SetActorTickEnabled(false);

	const FVector thisLoc = SpawnPoint->GetComponentLocation();
	const FVector birdLoc = SpawnedBird->GetActorLocation();
	const FVector diff = thisLoc - birdLoc;
	const float speed = diff.Length();

	if (FMath::IsNearlyEqual(speed, DistanceClamp.X, UE_DOUBLE_KINDA_SMALL_NUMBER))
	{
		SpawnedBird->Destroy();
		SpawnedBird = nullptr;
		return;
	}

	Birds.RemoveAt(0);
	SpawnedBird->Movement->Velocity = diff * ForceMultiplier;
	SpawnedBird->Movement->Activate();
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
	dir += birdQuat.GetUpVector() * direction.Y;

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
