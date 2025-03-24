// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UPanelWidget;

UCLASS()
class HUNGRYBIRDS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION() void OnQuitButtonClicked();

protected:

	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPanelWidget* LevelListHolder;
};
