// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoalMineCompositionTask.h"
#include "ParallelVisualizationComponent.h"
#include "CoalMineTaskControl_Parallel.generated.h"

UENUM(BlueprintType)
enum class ESuccessPolicy :uint8
{
	Policy_RequireOne UMETA(DisplayName = "One"),
	Policy_RequireAll UMETA(DisplayName="All")

};

UENUM(BlueprintType)
enum class EFailPolicy :uint8
{
	Policy_RequireOne UMETA(DisplayName = "One"),
	Policy_RequireAll UMETA(DisplayName = "All")

};

UCLASS()
class COALMINEPLATFORM_API ACoalMineTaskControl_Parallel : public ACoalMineCompositionTask
{
	GENERATED_BODY()
public:
	ACoalMineTaskControl_Parallel();

	//begin Coal mine Task Base interface
	virtual void OnInitialize_Implementation(ACoalMineTaskManager* NewTaskManager)override;

	virtual ETaskStatus OnUpdate_Implementation(float DeltaTime)override;

	virtual void Abort_Implementation()override;

	//end Coal mine Task Base interface

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = CoalMineTask)
		UParallelVisualizationComponent* ParallelVisualizationComponent;

private:
	void AbortCurrentTasks();
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=CoalMineTask)
	ESuccessPolicy SuccessPolicy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = CoalMineTask)
	EFailPolicy FailPolicy;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=CoalMineTask)
	bool bMigrateUnFinishedTasks;
private:
	UPROPERTY()
	TArray<ACoalMineTaskBase*> CurrentTasks;

	int FailedTaskCount;
};
