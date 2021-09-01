// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskControl.h"

// Sets default values
ACoalMineTaskControl::ACoalMineTaskControl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoalMineTaskControl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoalMineTaskControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoalMineTaskControl::ExecuteTasks() 
{
}

bool ACoalMineTaskControl::IsTasksFinish() 
{
	return false;
}
