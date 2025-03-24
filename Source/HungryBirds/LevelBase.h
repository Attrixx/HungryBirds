// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelBase.generated.h"

class UInputMappingContext;

class UTarget;

/**
 *
 */
UCLASS(Abstract)
class HUNGRYBIRDS_API ALevelBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;

public:

	void Register(UTarget* target);
	void Unregister(UTarget* target);

protected:

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenu;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> IMC;

	TArray<UTarget*> Targets;
};
