// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Target.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HUNGRYBIRDS_API UTarget : public UActorComponent
{
	GENERATED_BODY()

protected:

	UTarget();
	void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void Hit();
};
