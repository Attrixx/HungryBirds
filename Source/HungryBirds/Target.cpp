// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"
#include "LevelBase.h"
#include <Kismet/GameplayStatics.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(Target, Log, All);

UTarget::UTarget()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTarget::BeginPlay()
{
	Super::BeginPlay();

	OnTargetCreated.Broadcast(this);
}

void UTarget::Hit()
{
	OnTargetHit.Broadcast(this);
}
