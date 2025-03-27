// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedBird.h"
#include <GameFramework/ProjectileMovementComponent.h>

void ASpeedBird::OnSpecial()
{
	Movement->Velocity = Movement->Velocity.GetSafeNormal() * SpeedScale;
}
