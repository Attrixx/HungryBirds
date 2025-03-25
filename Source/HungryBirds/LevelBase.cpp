// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelBase.h"
#include <Logging/StructuredLog.h>

DEFINE_LOG_CATEGORY_STATIC(LevelBase, Log, All);

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

	if (Targets.IsEmpty())
	{
		OnLevelEnd();
	}
}

void ALevelBase::OnLevelEnd()
{
	UE_LOGFMT(LevelBase, Log, "Level End");
}
