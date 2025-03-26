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

	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOGFMT(Target, Error, "Component not spawned in a world!");
		return;
	}

	Level = Cast<ALevelBase>(UGameplayStatics::GetGameMode(world));
	if (!Level)
	{
		UE_LOGFMT(Target, Error, "Could not get level game mode!");
		return;
	}

	Level->Register(this);
}

void UTarget::Hit()
{
	if (!Level)
	{
		UE_LOGFMT(Target, Error, "Level not set!");
		return;
	}

	Level->Unregister(this);
}
