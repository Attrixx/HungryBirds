// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelInstanceWidget.h"
#include "Components/Button.h"
#include "../Utils.h"
#include <Engine/LevelStreamingDynamic.h>
#include <Kismet/GameplayStatics.h>
#include <Logging/StructuredLog.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "../GameManagerSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogLevelInstanceWidget, Log, All);

void ULevelInstanceWidget::OnLoadButtonClicked()
{
	UUtils::LoadLevel(Level, this);
}

void ULevelInstanceWidget::SetLevel(const TSoftObjectPtr<UWorld> World)
{
	Level = World;
	LevelNameHolder->SetText(FText::FromString(Level.GetAssetName()));
	uint8 HighScore = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetLevelHighScore(World.GetAssetName());

	StarImage1->SetBrushFromTexture((HighScore > 0) ? FullStarTexture : EmptyStarTexture);
	StarImage2->SetBrushFromTexture((HighScore > 1) ? FullStarTexture : EmptyStarTexture);
	StarImage3->SetBrushFromTexture((HighScore > 2) ? FullStarTexture : EmptyStarTexture);
}

void ULevelInstanceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadButton->OnClicked.AddDynamic(this, &ULevelInstanceWidget::OnLoadButtonClicked);
}
