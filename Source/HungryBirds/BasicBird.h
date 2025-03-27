// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BirdBase.h"
#include "BasicBird.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HUNGRYBIRDS_API ABasicBird : public ABirdBase
{
	GENERATED_BODY()
	
protected:

	void OnSpecial() override;
};
