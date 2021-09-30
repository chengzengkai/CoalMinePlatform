// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoalMineTaskBase.h"
#include "CoalMineCompositionTask.generated.h"

/**
 * 
 */
UCLASS()
class COALMINEPLATFORM_API ACoalMineCompositionTask : public ACoalMineTaskBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = CoalMineTask)
		TArray<ACoalMineTaskBase*>SubTasks;

};
