// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class HUNGRYBIRDS_API AMainMenu : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<ULevel>> Levels;
};
