// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalMineTaskManager.generated.h"

class ACoalMineTaskBase;
class ACoalMineTaskManager;

UENUM(BlueprintType)
enum class ETaskManagerStatus:uint8
{
	TaskManager_Idle UMETA(DisplayName="Idle"),
	TaskManager_Running UMETA(DisplayName="Running"),
	TaskManager_Success UMETA(DisplayName="Success"),
	TaskManager_Failure UMETA(DisplayName="Failure")
};

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

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=TaskManager)
	void StartLevel();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = TaskManager)
	void FinishLevel(ETaskManagerStatus NewStatus);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = TaskManager)
	void AbortLevel();

	UFUNCTION(BlueprintNativeEvent,Category=TaskManager)
	void OnLevelFinish(ETaskManagerStatus NewStatus);

	UFUNCTION(BlueprintNativeEvent, Category = TaskManager)
	void OnAbortLevel();
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

	UPROPERTY(BlueprintReadWrite, Category = TaskManager)
	ETaskManagerStatus Status;

private:
	UPROPERTY(Transient)
	TArray<ACoalMineTaskBase*> CurrentTasks;

};
