// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BirdBase.h"
#include "SpeedBird.generated.h"

/**
 *
 */
UCLASS()
class HUNGRYBIRDS_API ASpeedBird : public ABirdBase
{
	GENERATED_BODY()

	void OnSpecial() override;

public:
	UPROPERTY(EditAnywhere)
	float SpeedScale;
};
