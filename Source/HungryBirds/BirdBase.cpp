// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdBase.h"
#include <EnhancedInputComponent.h>
#include <Logging/StructuredLog.h>
#include <GameFramework/ProjectileMovementComponent.h>

DEFINE_LOG_CATEGORY_STATIC(BirdBase, Log, All);

ABirdBase::ABirdBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->bRotationFollowsVelocity = true;
	Movement->bAutoActivate = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->OnComponentHit.AddDynamic(this, &ABirdBase::OnActorHit);

}

void ABirdBase::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ABirdBase::Setup(APawn* slinger)
{
	Slinger = slinger;
	Slinger->GetController()->Possess(this);
}

void ABirdBase::ExecuteSpecial()
{
	if (SpecialUses > 0)
	{
		--SpecialUses;
		OnSpecial();
	}
}

void ABirdBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& Hit)
{
	SpecialUses = 0;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABirdBase::OnTimerEnd, DestroyTimerAfterHit, false);
}

void ABirdBase::OnTimerEnd()
{
	GetController()->Possess(Slinger);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

