// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "BirdBase.h"
#include <Logging/StructuredLog.h>
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputComponent.h>

DEFINE_LOG_CATEGORY_STATIC(DefaultPlayerController, Log, All);

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!playerController)
	{
		UE_LOGFMT(DefaultPlayerController, Error, "Could not get PlayerController");
		return;
	}

	UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(playerController->InputComponent);
	if (!eic)
	{
		UE_LOGFMT(DefaultPlayerController, Error, "Could not cast EnhancedInputComponent");
		return;
	}

	eic->BindAction(SpecialAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnSpecial);
}

void ADefaultPlayerController::OnSpecial()
{
	if (auto* bird = Cast<ABirdBase>(GetPawn()))
	{
		UE_LOGFMT(DefaultPlayerController, Log, "Special triggered!");
		bird->OnSpecial();
	}
}
