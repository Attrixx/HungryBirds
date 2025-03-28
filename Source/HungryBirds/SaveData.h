#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.generated.h"

UCLASS()
class HUNGRYBIRDS_API USaveData : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TMap<FString, uint8> ScoreByLevel;
};