// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalMineTaskManager.generated.h"

class ACoalMineTaskBase;
class ACoalMineTaskManager;

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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = TaskManager)
	class UBillboardComponent* BillboardComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = TaskManager)
	class UManagerVisualizationComponent* TaskManagerVisualizationComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TaskManager)
	ACoalMineTaskBase* InitialTask;

private:
	UPROPERTY(Transient)
	TArray<ACoalMineTaskBase*> CurrentTasks;

};
