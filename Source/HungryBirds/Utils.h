#pragma once

#include "CoreMinimal.h"

class HUNGRYBIRDS_API UUtils
{
public:

	static void LoadLevel(const TSoftObjectPtr<UWorld>& LevelToLoad, UObject* WorldContext);
};