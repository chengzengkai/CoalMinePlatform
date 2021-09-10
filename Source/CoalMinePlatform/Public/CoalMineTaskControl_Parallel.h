// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoalMineCompositionTask.h"
#include "ParallelVisualizationComponent.h"
#include "CoalMineTaskControl_Parallel.generated.h"

/**
 * 
 */
UCLASS()
class COALMINEPLATFORM_API ACoalMineTaskControl_Parallel : public ACoalMineCompositionTask
{
	GENERATED_BODY()
public:
	ACoalMineTaskControl_Parallel();

	virtual void OnInitialize_Implementation(ACoalMineTaskManager* NewTaskManager)override;

	virtual ETaskStatus OnUpdate_Implementation(float DeltaTime)override;

	virtual void Abort_Implementation()override;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = CoalMineTask)
		UParallelVisualizationComponent* ParallelVisualizationComponent;

private:
	UPROPERTY()
	ACoalMineTaskBase* CurrentTask;

	int CurrentTaskIndex;
};
