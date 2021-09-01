// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoalMineTaskInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCoalMineTaskInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COALMINEPLATFORM_API ICoalMineTaskInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, Category = "CoalMineTaskInterface")
	void OnInitialize();

	UFUNCTION(BlueprintImplementableEvent, Category = "CoalMineTaskInterface")
	void OnTaskAbort();

	UFUNCTION(BlueprintImplementableEvent, Category = "CoalMineTaskInterface")
	void OnTaskFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CoalMineTaskInterface")
	bool IsTaskFinished();

};
