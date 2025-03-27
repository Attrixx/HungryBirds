// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdBase.h"
#include <EnhancedInputComponent.h>
#include <Logging/StructuredLog.h>
#include <GameFramework/ProjectileMovementComponent.h>

DEFINE_LOG_CATEGORY_STATIC(BirdBase, Log, All);

ABirdBase::ABirdBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->bRotationFollowsVelocity = true;
	Movement->bAutoActivate = false;
}

void ABirdBase::Setup(APawn* slinger)
{
	Slinger = slinger;
	Slinger->GetController()->Possess(this);
}

