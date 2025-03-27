// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBase.h"
#include "Target.h"
#include "Utils.h"
#include "GameManagerSubsystem.h"
#include <Logging/StructuredLog.h>
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY_STATIC(LevelBase, Log, All);

ALevelBase* ALevelBase::GetInstance(const UObject* worldContext)
{
	return Cast<ALevelBase>(UGameplayStatics::GetGameState(worldContext));
}

void ALevelBase::Register(UTarget* target)
{
	Targets.Add(target);
}

void ALevelBase::Unregister(UTarget* target)
{
	int32 count = Targets.RemoveSwap(target);
	if (count == 0)
	{
		UE_LOGFMT(LevelBase, Warning, "Unregister did not remove any reference!");
	}

	currentScore += count;

	if (Targets.IsEmpty())
	{
		OnLevelEnd();
	}
}

void ALevelBase::OnLevelEnd()
{
	auto GameManager = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	GameManager->RegisterScore(GetWorld()->GetName(), currentScore, true);
	UUtils::LoadLevel(MainMenu, GetWorld());
}
