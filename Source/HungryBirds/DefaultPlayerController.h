// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS(Abstract)
class HUNGRYBIRDS_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	void BeginPlay() override;

private:

	void OnSpecial();

protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> SpecialAction;
};
