// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelInstanceWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class HUNGRYBIRDS_API ULevelInstanceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION() void OnLoadButtonClicked();
	void SetLevel(const TSoftObjectPtr<UWorld> World);

protected:
	
	virtual void NativeConstruct() override;

public:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> LoadButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelNameHolder;

	UPROPERTY()
	TSoftObjectPtr<UWorld> Level;

};
