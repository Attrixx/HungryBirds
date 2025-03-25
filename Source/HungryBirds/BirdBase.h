// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BirdBase.generated.h"

UCLASS(Abstract)
class HUNGRYBIRDS_API ABirdBase : public ACharacter
{
	GENERATED_BODY()

protected:

	ABirdBase();

public:

	virtual void OnSpecial() PURE_VIRTUAL(&ABirdBase::OnSpecial, )
};
