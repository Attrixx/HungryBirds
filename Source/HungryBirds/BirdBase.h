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
	void EndPlay(EEndPlayReason::Type reason) override;

public:

	void Setup(APawn* slinger);
	void ExecuteSpecial();

protected:

	virtual void OnSpecial() PURE_VIRTUAL(&ABirdBase::OnSpecial, );

private:

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& Hit);
	void OnTimerEnd();

public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> Movement;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	float DestroyTimerAfterHit;

	UPROPERTY(EditAnywhere)
	int32 SpecialUses = 1;

private:

	APawn* Slinger;
	FTimerHandle TimerHandle;
};
