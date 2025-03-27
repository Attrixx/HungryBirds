// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdBase.generated.h"

class UProjectileMovementComponent;

UCLASS(Abstract, NotBlueprintable)
class HUNGRYBIRDS_API ABirdBase : public APawn
{
	GENERATED_BODY()

protected:

	ABirdBase();

public:

	void Setup(APawn* slinger);

	virtual void OnSpecial() PURE_VIRTUAL(&ABirdBase::OnSpecial, );

public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> Movement;

private:

	APawn* Slinger;
};
