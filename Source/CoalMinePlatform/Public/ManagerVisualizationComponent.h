// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "ManagerVisualizationComponent.generated.h"

class ACoalMineTaskBase;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = (Physics, Collision, Lighting, Rendering, Tags, Activation, Cooking, Input, Actor, HLOD, Mobile))
class COALMINEPLATFORM_API UManagerVisualizationComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
public:
	UManagerVisualizationComponent();

protected:

	virtual FPrimitiveSceneProxy* CreateSceneProxy()override;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld)const override;

public:
	ACoalMineTaskBase* GetOwnerInitialTask()const;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ManagerVisualization)
		float LineThickness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ManagetVisualization)
		FColor LineColor;


	
};
