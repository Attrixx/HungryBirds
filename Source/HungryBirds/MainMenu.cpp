// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include <Logging/StructuredLog.h>
#include <EnhancedInputSubsystems.h>

DEFINE_LOG_CATEGORY_STATIC(MainMenu, Log, All);

void AMainMenu::BeginPlay()
{
	if (!IMC)
	{
		UE_LOGFMT(MainMenu, Error, "No InputMappingContext set");
		return;
	}

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (!playerController)
	{
		UE_LOGFMT(MainMenu, Error, "Could not get the player controller");
		return;
	}

	auto* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	if (!inputSubsystem)
	{
		UE_LOGFMT(MainMenu, Error, "Could not get the input subsystem");
		return;
	}

	inputSubsystem->AddMappingContext(IMC, 0);
	UE_LOGFMT(MainMenu, Log, "Input enabled.");
}
