// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HUNGRYBIRDS_API AMainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:

	const TArray<TSoftObjectPtr<UWorld>>& GetLevels();
	
protected:

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UWorld>> Levels;
};
