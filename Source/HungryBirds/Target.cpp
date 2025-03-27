// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"
#include "LevelBase.h"
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(Target, Log, All);

UTarget::UTarget()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTarget::BeginPlay()
{
	Super::BeginPlay();

	if (auto* level = ALevelBase::GetInstance(GetWorld()))
	{
		level->Register(this);
	}
	else
	{
		UE_LOGFMT(Target, Warning, "Could not get level instance");
	}
}

void UTarget::Hit()
{
	if (auto* level = ALevelBase::GetInstance(GetWorld()))
	{
		level->Unregister(this);
	}
	else
	{
		UE_LOGFMT(Target, Warning, "Could not get level instance");
	}
}
