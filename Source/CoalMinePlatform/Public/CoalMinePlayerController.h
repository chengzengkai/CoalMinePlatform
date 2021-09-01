// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CoalMinePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COALMINEPLATFORM_API ACoalMinePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;
	
};
