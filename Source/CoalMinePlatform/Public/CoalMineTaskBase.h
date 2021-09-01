// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalMineTaskInterface.h"
#include "CoalMineTaskBase.generated.h"

UCLASS()
class COALMINEPLATFORM_API ACoalMineTaskBase : public AActor,public ICoalMineTaskInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoalMineTaskBase();

	virtual bool IsTaskFinished_Implementation();

	UFUNCTION(BlueprintCallable,Category="CoalMine Task")
		void SetTaskFinish() { bTaskFinished = true; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoTask();

private:

	bool bTaskFinished;

};
