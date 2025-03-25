// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelBase.generated.h"

class UTarget;

/**
 *
 */
UCLASS(Abstract)
class HUNGRYBIRDS_API ALevelBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	void Register(UTarget* target);
	void Unregister(UTarget* target);

private:

	void OnLevelEnd();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenu;

	TArray<UTarget*> Targets;
};
