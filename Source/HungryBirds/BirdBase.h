// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdBase.generated.h"

UCLASS(Abstract)
class HUNGRYBIRDS_API ABirdBase : public APawn
{
	GENERATED_BODY()

protected:

	ABirdBase();

public:

	virtual void OnSpecial() PURE_VIRTUAL(&ABirdBase::OnSpecial, )
};
