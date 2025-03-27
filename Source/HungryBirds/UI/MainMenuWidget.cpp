// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include <Components/Button.h>
#include "Kismet/KismetSystemLibrary.h"
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

	AMainMenu* mainMenu = AMainMenu::GetInstance(GetWorld());
	if (!mainMenu)
	{
		UE_LOGFMT(LogMainMenuWidget, Error, "Could not retrieve Game State");
		return;
	}

	for (auto& level : mainMenu->GetLevels())
	{
		ULevelInstanceWidget* levelWidgetInstance = CreateWidget<ULevelInstanceWidget>(GetWorld(), LevelWidgetClass);
		levelWidgetInstance->SetLevel(level);
		LevelListHolder->AddChild(levelWidgetInstance);
	}
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}