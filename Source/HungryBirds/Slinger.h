// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Slinger.generated.h"

struct FInputActionValue;
class ABirdBase;
class UInputAction;

UCLASS(Abstract)
class HUNGRYBIRDS_API ASlinger : public APawn
{
	GENERATED_BODY()

protected:

	ASlinger();
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Tick(float dt) override;

private:

	void OnAimStart();
	void OnAimEnd();
	void OnAimDirection(const FInputActionValue& value);
	void OnAimForce(const FInputActionValue& value);

protected:

	UPROPERTY(EditInstanceOnly)
	TArray<TSubclassOf<ABirdBase>> Birds;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AimHoldAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AimDirectionAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AimForceAction;

	// Spawn points of birds
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USceneComponent> SpawnPoint;

	UPROPERTY(EditAnywhere)
	FVector2D DistanceClamp = {1., 60.};

	UPROPERTY(EditAnywhere)
	float ForceMultiplier = 100.f;

private:

	TObjectPtr<ABirdBase> SpawnedBird;
};
