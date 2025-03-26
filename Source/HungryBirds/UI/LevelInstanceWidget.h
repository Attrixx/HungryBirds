// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelInstanceWidget.generated.h"

class UButton;

UCLASS()
class HUNGRYBIRDS_API ULevelInstanceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION() void OnLoadButtonClicked();
	void SetLevel(const TObjectPtr<UWorld> World);

protected:
	
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* LoadButton;

	UPROPERTY()
	TObjectPtr<UWorld> Level;
};
