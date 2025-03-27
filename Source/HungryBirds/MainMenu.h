// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HUNGRYBIRDS_API AMainMenu : public AGameStateBase
{
	GENERATED_BODY()

public:

	static AMainMenu* GetInstance(const UObject* worldContext);

	const TArray<TSoftObjectPtr<UWorld>>& GetLevels();
	
protected:

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UWorld>> Levels;
};
