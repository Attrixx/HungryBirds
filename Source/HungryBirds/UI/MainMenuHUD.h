// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMainMenuWidget;

UCLASS(Abstract)
class HUNGRYBIRDS_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY()
	UMainMenuWidget* MainMenuWidget;
};
