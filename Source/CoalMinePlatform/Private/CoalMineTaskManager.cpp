// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskManager.h"
#include "Components/BillboardComponent.h"

// Sets default values
ACoalMineTaskManager::ACoalMineTaskManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BillboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));
	BillboardComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACoalMineTaskManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoalMineTaskManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACoalMineTaskManager::ExecuteTasks() 
{
	
}

bool ACoalMineTaskManager::IsTasksFinish() 
{
	return false;
}
