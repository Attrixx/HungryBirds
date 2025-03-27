#include "GameManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "SaveData.h"
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(GameManagerSubsystemLog, Log, All);

void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LoadGame();
}

void UGameManagerSubsystem::Deinitialize()
{
	SaveGame();
	Super::Deinitialize();
}

uint8 UGameManagerSubsystem::GetLevelHighScore(const FString& LevelName)
{
	if (!DataCheck())
	{
		return 0;
	}

	if (!SaveData->ScoreByLevel.Contains(LevelName))
	{
		return 0;
	}

	return SaveData->ScoreByLevel[LevelName];
}

void UGameManagerSubsystem::RegisterScore(FString LevelName, uint8 Score, bool bSaveWhenDone)
{
	if (!DataCheck())
	{
		return;
	}

	if (SaveData->ScoreByLevel.Contains(LevelName))
	{
		if (SaveData->ScoreByLevel[LevelName] < Score)
		{
			SaveData->ScoreByLevel[LevelName] = Score;
		}
	}
	else
	{
		SaveData->ScoreByLevel.Add(LevelName, Score);
	}

	if (bSaveWhenDone)
	{
		SaveGame();
	}
}

void UGameManagerSubsystem::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist("SaveData", 0))
	{
		SaveData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0));
		if (SaveData)
		{
			UE_LOGFMT(GameManagerSubsystemLog, Log, "Loaded SaveData successfully.");
		}
		else
		{
			UE_LOGFMT(GameManagerSubsystemLog, Warning, "Failed to load SaveData. Creating new file.");
			SaveData = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));
		}
	}
	else
	{
		UE_LOGFMT(GameManagerSubsystemLog, Log, "SaveData file not found. Creating new file.");
		SaveData = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));
	}
}

bool UGameManagerSubsystem::DataCheck()
{
	if (!SaveData)
	{
		UE_LOGFMT(GameManagerSubsystemLog, Warning, "Failed to perform action. SaveData is null.");
		return false;
	}
	return true;
}

void UGameManagerSubsystem::SaveGame()
{
	if (!SaveData)
	{
		UE_LOGFMT(GameManagerSubsystemLog, Warning, "Failed to save SaveData. SaveData is null.");
		return;
	}

	UGameplayStatics::SaveGameToSlot(SaveData, "SaveData", 0);
	UE_LOGFMT(GameManagerSubsystemLog, Log, "Saved SaveData successfully.");
}
