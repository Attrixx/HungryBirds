// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UPanelWidget;
class ULevelInstanceWidget;

UCLASS()
class HUNGRYBIRDS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION() void OnQuitButtonClicked();

protected:

	virtual void NativeConstruct() override;

public:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UPanelWidget> LevelListHolder;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULevelInstanceWidget> LevelWidgetClass;
};
