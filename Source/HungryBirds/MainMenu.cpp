// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(MainMenu, Log, All);

const TArray<TSoftObjectPtr<UWorld>>& AMainMenu::GetLevels()
{
    return Levels;
}
