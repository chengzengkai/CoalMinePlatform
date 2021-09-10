// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "SequentialVisualizationComponent.generated.h"

class ACoalMineTaskBase;
/**
 * 
 */
UCLASS()
class COALMINEPLATFORM_API USequentialVisualizationComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
public:
	USequentialVisualizationComponent();
protected:
	virtual void BeginPlay()override;

	virtual FPrimitiveSceneProxy* CreateSceneProxy()override;

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld)const override;

public:
	TArray<ACoalMineTaskBase*> GetOwnerSubTasks() const;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TaskSequentialVisualization)
		float LineThickness;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TaskSequentialVisualization)
		FColor LineColor;

};
