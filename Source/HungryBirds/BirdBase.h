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
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& Hit);
	virtual void OnSpecial() PURE_VIRTUAL(&ABirdBase::OnSpecial, );
	void EndPlay(EEndPlayReason::Type reason) override;
private:
	void OnTimer();


public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> Movement;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	float DestroyTimerAfterHit;

private:

	APawn* Slinger;
	FTimerHandle TimerHandle;
protected:
	bool CanUseSpecial = true;
};
