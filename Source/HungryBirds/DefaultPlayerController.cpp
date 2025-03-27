// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "BirdBase.h"
#include <Logging/StructuredLog.h>
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

DEFINE_LOG_CATEGORY_STATIC(DefaultPlayerController, Log, All);

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;

	UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(InputComponent);
	if (!eic)
	{
		UE_LOGFMT(DefaultPlayerController, Error, "Could not cast EnhancedInputComponent");
		return;
	}

	eic->BindAction(SpecialAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnSpecial);

	if (auto* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		inputSubsystem->AddMappingContext(IMC, 0);
		UE_LOGFMT(DefaultPlayerController, Log, "Inputs enabled.");
	}
}

void ADefaultPlayerController::OnSpecial()
{
 	if (auto* bird = Cast<ABirdBase>(GetPawn()))
	{
		UE_LOGFMT(DefaultPlayerController, Log, "Special triggered!");
		bird->OnSpecial();
	}
}
