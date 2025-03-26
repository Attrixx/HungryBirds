// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <Logging/StructuredLog.h>

#include "LevelInstanceWidget.h"
#include "../MainMenu.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainMenuWidget, Log, All);

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitButtonClicked);
	}

	if (!LevelWidgetClass)
	{
		UE_LOGFMT(LogMainMenuWidget, Error, "LevelWidget is nullptr");
		return;
	}

	AMainMenu* GameMode = Cast<AMainMenu>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		UE_LOGFMT(LogMainMenuWidget, Error, "Could not retrieve Game Mode");
		return;
	}

	for (auto& Level : GameMode->GetLevels())
	{
		ULevelInstanceWidget* LevelWidgetInstance = CreateWidget<ULevelInstanceWidget>(GetWorld(), LevelWidgetClass);
		LevelWidgetInstance->SetLevel(Level);
		LevelListHolder->AddChild(LevelWidgetInstance);
	}
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}