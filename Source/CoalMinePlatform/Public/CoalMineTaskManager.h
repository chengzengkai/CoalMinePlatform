// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalMineTaskManager.generated.h"

class ACoalMineTaskControl;
UCLASS(hidecategories = (Rendering))
class COALMINEPLATFORM_API ACoalMineTaskManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoalMineTaskManager();

	virtual void ExecuteTasks();

	virtual bool IsTasksFinish();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	class UBillboardComponent* BillboardComp;

private:
	UPROPERTY(EditInstanceOnly)
	TArray<ACoalMineTaskControl*> TaskControls;

};
