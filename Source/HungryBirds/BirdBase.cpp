// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdBase.h"
#include <EnhancedInputComponent.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(BirdBase, Log, All);

ABirdBase::ABirdBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABirdBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(InputComponent);
	if (!eic)
	{
		UE_LOGFMT(BirdBase, Error, "Could not cast to EnhancedInputComponent");
		return;
	}

	eic->BindAction(SpecialAction, ETriggerEvent::Triggered, this, &ABirdBase::OnSpecial);
}
