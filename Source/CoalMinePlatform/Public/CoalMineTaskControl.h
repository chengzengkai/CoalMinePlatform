// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoalMineTaskManager.h"
#include "CoalMineTaskControl.generated.h"

class ACoalMineTaskBase;
UCLASS()
class COALMINEPLATFORM_API ACoalMineTaskControl : public ACoalMineTaskManager
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoalMineTaskControl();

	virtual void ExecuteTasks()override;

	virtual bool IsTasksFinish()override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditInstanceOnly)
	TArray<ACoalMineTaskBase*> TasksList;
};
