// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBase.h"
#include <Logging/StructuredLog.h>
#include <EnhancedInputSubsystems.h>

DEFINE_LOG_CATEGORY_STATIC(LevelBase, Log, All);


void ALevelBase::BeginPlay()
{
	if (!IMC)
	{
		UE_LOGFMT(LevelBase, Error, "No InputMappingContext set");
		return;
	}

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (!playerController)
	{
		UE_LOGFMT(LevelBase, Error, "Could not get the player controller");
		return;
	}

	auto* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	if (!inputSubsystem)
	{
		UE_LOGFMT(LevelBase, Error, "Could not get the input subsystem");
		return;
	}

	inputSubsystem->AddMappingContext(IMC, 0);
	UE_LOGFMT(LevelBase, Log, "Input enabled.");
}


void ALevelBase::Register(UTarget* target)
{
	Targets.Add(target);
}

void ALevelBase::Unregister(UTarget* target)
{
	int32 count = Targets.RemoveSwap(target);
	if (count == 0)
	{
		UE_LOGFMT(LevelBase, Warning, "Unregister did not remove any reference!");
	}
}
