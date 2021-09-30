// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "CoalMineTaskBase.generated.h"

class ACoalMineTaskManager;

UENUM(BlueprintType)
enum class ETaskStatus :uint8
{
	Idle,
	Running,
	Success,
	Failure
};

UCLASS(HideCategories = (Physics, Collision, Lighting, Rendering, Activation, Cooking, Input, HLOD, Mobile))
class COALMINEPLATFORM_API ACoalMineTaskBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoalMineTaskBase();

public:
	// Task initialize 
	UFUNCTION(BlueprintNativeEvent, Category = "CoalMine Task")
	void OnInitialize(ACoalMineTaskManager* NewManager);
	virtual void OnInitialize_Implementation(ACoalMineTaskManager* NewManager);

	//Task Update Logic,tick to update task status
	UFUNCTION(BlueprintNativeEvent, Category = "CoalMine Task")
	ETaskStatus OnUpdate(float DeltaTime);
	virtual ETaskStatus OnUpdate_Implementation(float DeltaTime);

	//task finish callback 
	UFUNCTION(BlueprintNativeEvent, Category = "CoalMine Task")
	void OnFinish();
	virtual void OnFinish_Implementation();

	//abort task 
	UFUNCTION(BlueprintNativeEvent, Category = "CoalMine Task")
	void Abort();
	virtual void Abort_Implementation();

public:
	UPROPERTY(BlueprintReadWrite, Category = "CoalMine Task")
	ETaskStatus Status;

	UPROPERTY(BlueprintReadOnly, Category = "CoalMine Task")
	ACoalMineTaskManager* TaskManager;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = GameplayLevelTask)
		USceneComponent* RootComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = GameplayLevelTask)
		UBillboardComponent* BillBoardComp;
};
