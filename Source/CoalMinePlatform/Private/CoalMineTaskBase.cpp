// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskBase.h"

// Sets default values
ACoalMineTaskBase::ACoalMineTaskBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoalMineTaskBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoalMineTaskBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoalMineTaskBase::DoTask()
{
}


bool ACoalMineTaskBase::IsTaskFinished_Implementation()
{
	return false;
}