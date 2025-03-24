// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdBase.generated.h"

class UInputAction;

UCLASS(Abstract)
class HUNGRYBIRDS_API ABirdBase : public APawn
{
	GENERATED_BODY()

protected:

	ABirdBase();
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	virtual void OnSpecial() PURE_VIRTUAL(&ABirdBase::OnSpecial, )

protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> SpecialAction;
};
