// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Slinger.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS()
class HUNGRYBIRDS_API ASlinger : public APawn
{
	GENERATED_BODY()

protected:

	ASlinger();
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void OnAimDirection(const FInputActionValue& value);
	void OnAimForce(const FInputActionValue& value);

protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> AimDirectionAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> AimForceAction;
};
