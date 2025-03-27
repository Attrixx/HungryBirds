// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBase.h"
#include "Target.h"
#include "Utils.h"
#include "GameManagerSubsystem.h"
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(LevelBase, Log, All);

void ALevelBase::BeginPlay()
{
	Super::BeginPlay();

	RegHandle = UTarget::OnTargetCreated.AddUObject(this, &ALevelBase::Register);
	UnregHandle = UTarget::OnTargetHit.AddUObject(this, &ALevelBase::Unregister);
}

void ALevelBase::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason); 

	UTarget::OnTargetCreated.Remove(RegHandle);
	UTarget::OnTargetHit.Remove(UnregHandle);
}

void ALevelBase::Register(UTarget* target)
{
	Targets.Add(target);
}

void ALevelBase::Unregister(UTarget* target)
{
	++currentScore;

	int32 count = Targets.RemoveSwap(target);
	if (count == 0)
	{
		UE_LOGFMT(LevelBase, Warning, "Unregister did not remove any reference!");
	}

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
