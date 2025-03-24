// Fill out your copyright notice in the Description page of Project Settings.

#include "Slinger.h"
#include <EnhancedInputComponent.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(Slinger, Log, All);

ASlinger::ASlinger()
{
	PrimaryActorTick.bCanEverTick = false;
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

	eic->BindAction(AimDirectionAction, ETriggerEvent::Triggered, this, &ASlinger::OnAimDirection);
	eic->BindAction(AimForceAction, ETriggerEvent::Triggered, this, &ASlinger::OnAimForce);
}

void ASlinger::OnAimDirection(const FInputActionValue& value)
{
	auto direction = value.Get<FVector2D>();

	// TODO
}

void ASlinger::OnAimForce(const FInputActionValue& value)
{
	auto force = value.Get<float>();

	// TODO
}
