#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManagerSubsystem.generated.h"

class USaveData;

UCLASS()
class HUNGRYBIRDS_API UGameManagerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
	
	void RegisterScore(FString LevelName, uint8 Score, bool bSaveWhenDone);
	void SaveGame();

private:

	bool DataCheck();
	void LoadGame();

private:

    UPROPERTY()
	USaveData* SaveData;
};