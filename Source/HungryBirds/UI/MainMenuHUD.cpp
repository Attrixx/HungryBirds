// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "MainMenuWidget.h"
#include <Blueprint/UserWidget.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(LogMainMenuHUD, Log, All);

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!MainMenuWidgetClass)
	{
		UE_LOGFMT(LogMainMenuHUD, Error, "MainMenuWidgetClass is nullptr in MainMenuHUD");
		return;
	}

	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();

	auto* Controller = GetWorld()->GetFirstPlayerController();
	Controller->bShowMouseCursor = true;
	Controller->SetInputMode(FInputModeUIOnly{});
}