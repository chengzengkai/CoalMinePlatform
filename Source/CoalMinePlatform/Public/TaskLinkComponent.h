// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "TaskLinkComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class COALMINEPLATFORM_API UTaskLinkComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
public:
	UTaskLinkComponent() {};

protected:
	virtual FPrimitiveSceneProxy* CreateSceneProxy()override;

public:


};
