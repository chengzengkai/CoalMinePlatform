// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CoalMineSubsystem.generated.h"
class ULevelSequence;
/**
 * 
 */
UCLASS()
class COALMINEPLATFORM_API UCoalMineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize()override;

	UFUNCTION(BlueprintCallable, Category = "CoalMineSubsystem")
		void PlaySequence(ULevelSequence* Sequence);
	
};
