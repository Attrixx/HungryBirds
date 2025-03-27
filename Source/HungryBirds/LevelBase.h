// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LevelBase.generated.h"

class UTarget;

/**
 *
 */
UCLASS(Abstract)
class HUNGRYBIRDS_API ALevelBase : public AGameStateBase
{
	GENERATED_BODY()

public:

	static ALevelBase* GetInstance(const UObject* worldContext);

	void Register(UTarget* target);
	void Unregister(UTarget* target);

	void OnLevelEnd();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenu;

	TArray<UTarget*> Targets;
};
