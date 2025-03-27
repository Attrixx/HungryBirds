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

	void OnLevelEnd();

protected:

	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type) override;

private:

	void Register(UTarget* target);
	void Unregister(UTarget* target);

protected:

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenu;

	TArray<UTarget*> Targets;


private:

	int8 currentScore = 0;
	FDelegateHandle RegHandle, UnregHandle;
};
