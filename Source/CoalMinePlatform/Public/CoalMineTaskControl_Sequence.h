// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoalMineCompositionTask.h"
#include "SequentialVisualizationComponent.h"
#include "CoalMineTaskControl_Sequence.generated.h"

/**
 * 
 */
UCLASS()
class COALMINEPLATFORM_API ACoalMineTaskControl_Sequence : public ACoalMineCompositionTask
{
	GENERATED_BODY()
public:
	ACoalMineTaskControl_Sequence();

	virtual void OnInitialize_Implementation(ACoalMineTaskManager* NewTaskManager)override;

	virtual ETaskStatus OnUpdate_Implementation(float DeltaTime)override;

	virtual void Abort_Implementation()override;

private:
	void AbortCurrentTasks();

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"),Category = CoalMineTask)
	USequentialVisualizationComponent* SequentialVisualizationComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = CoalMineTask)
	bool bContinueWhenSubTaskFailed;
private:
	UPROPERTY()
	ACoalMineTaskBase* CurrentTask;

	int CurrentTaskIndex;

};
