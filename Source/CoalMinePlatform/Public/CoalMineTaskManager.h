// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalMineTaskManager.generated.h"

class ACoalMineTaskBase;

UCLASS(hidecategories = (Rendering))
class COALMINEPLATFORM_API ACoalMineTaskManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoalMineTaskManager();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ExecuteTasks();

	virtual bool IsTasksFinish();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	class UBillboardComponent* BillboardComp;

private:
	UPROPERTY(Transient)
	TArray<ACoalMineTaskBase*> CurrentTasks;

};
