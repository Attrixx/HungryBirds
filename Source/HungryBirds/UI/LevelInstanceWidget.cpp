// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelInstanceWidget.h"
#include "Components/Button.h"
#include "../Utils.h"
#include <Engine/LevelStreamingDynamic.h>
#include <Kismet/GameplayStatics.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(LogLevelInstanceWidget, Log, All);

void ULevelInstanceWidget::OnLoadButtonClicked()
{
	if (!Level)
	{
		UE_LOGFMT(LogLevelInstanceWidget, Error, "LevelScene is not set!");
		return;
	}

	UUtils::LoadLevel(Level, this);
}

void ULevelInstanceWidget::SetLevel(const TSoftObjectPtr<UWorld> World)
{
	Level = World;
}

void ULevelInstanceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadButton->OnClicked.AddDynamic(this, &ULevelInstanceWidget::OnLoadButtonClicked);
}
