// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include <Logging/StructuredLog.h>
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY_STATIC(MainMenu, Log, All);

AMainMenu* AMainMenu::GetInstance(const UObject* worldContext)
{
    return Cast<AMainMenu>(UGameplayStatics::GetGameState(worldContext));
}

const TArray<TSoftObjectPtr<UWorld>>& AMainMenu::GetLevels()
{
    return Levels;
}
