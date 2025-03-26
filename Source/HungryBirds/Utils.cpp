#include "Utils.h"
#include <Kismet/GameplayStatics.h>
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(LogUtils, Log, All);

void UUtils::LoadLevel(const TSoftObjectPtr<UWorld>& LevelToLoad, UObject* WorldContext)
{
	if (!LevelToLoad)
	{
		UE_LOGFMT(LogUtils, Error, "LevelToLoad is not set!");
		return;
	}

	FString LevelPath = LevelToLoad->GetOutermost()->GetName();
	if (LevelPath.IsEmpty())
	{
		UE_LOGFMT(LogUtils, Error, "Invalid LevelToLoad path!");
		return;
	}

	UGameplayStatics::OpenLevel(WorldContext, FName(*LevelPath));
}